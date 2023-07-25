#include "s21_decimal.h"

int getScale(float src) {
  int scale = 0;
  long long unsigned int temp = 0;
  if (src < 0) src = -src;
  while (1) {
    temp = src;
    if ((src - temp) != 0) {
      src = src * 10;
      scale++;
    } else
      break;
  }
  return scale;
}
int getExp(int bit3) {
  int exp = 0xFF;
  bit3 = bit3 >> 16;
  exp = exp & bit3;
  return exp;
}

int setBit(int index, s21_decimal *dst) {
  int error = 0;
  long long unsigned int bit = pow(2, index % 32);
  // printf("\n\n text = %d \n\n", bit);
  if ((index >= 0) && (index <= 31))
    dst->bits[0] |= bit;
  else if ((index >= 32) && (index <= 63))
    dst->bits[1] |= bit;
  else if ((index >= 64) && (index <= 95))
    dst->bits[2] |= bit;
  else if ((index >= 96) && (index <= 127))
    dst->bits[3] |= bit;
  else
    error = 1;
  return error;
}

void get_bits(s21_decimal obj) {
  for (int i = 0; i <= 95; i++) {
    printf("%d", get_bit(obj, i));
  }
}

void set_bit(s21_decimal *obj, int j) { obj->bits[j / 32] |= (1 << (j % 32)); }

s21_decimal setShift(s21_decimal dst, int j) {
  for (int i = 0; i < j; i++) {
    int chek1 = 0, chek2 = 0;
    if (get_bit(dst, 63) == 1 && chek2 != 1) {
      dst.bits[2] = dst.bits[2] << 1;
      chek2 = 1;
      setBit(64, &dst);
    }

    if (get_bit(dst, 31) == 1) {
      if (get_bit(dst, 63) == 1 && chek2 != 1) {
        dst.bits[2] = dst.bits[2] << 1;
        chek2 = 1;
        setBit(64, &dst);
      }
      chek1 = 1;
      dst.bits[1] = dst.bits[1] << 1;
      setBit(32, &dst);
    }

    dst.bits[0] = dst.bits[0] << 1;
    if (chek1 != 1) {
      dst.bits[1] = dst.bits[1] << 1;
    }
    if (chek2 != 1) {
      dst.bits[2] = dst.bits[2] << 1;
    }
  }
  return dst;
}

void removeBit(int j, s21_decimal *dst) {
  dst->bits[j / 32] &= ~(1 << (j % 32));
}

int getSignInt(int src) {
  int sign = 0;
  sign = -1 * (src >> 31);
  return sign;
}
void setSignInt(int sign, s21_decimal *dst) {  //!!!!
  if (sign == 1) {
    dst->bits[3] |= MINUS;
  } else if (sign == 0) {
    dst->bits[3] &= PLUS;
  }
}
int get_bit(s21_decimal value, int i) {
  unsigned int mask = 1u << (i % 32);  // 1u - это unsigned int 1
  return (!!(value.bits[i / 32] & mask));
}

s21_decimal add_function(s21_decimal value_1, s21_decimal value_2,
                         int subFlag) {
  int temp = 0;
  s21_decimal result = {{0, 0, 0, value_1.bits[3]}};
  if (subFlag == 1) {
    if (value_1.bits[0] < value_2.bits[0]) {
      if (value_1.bits[1] == 0) {
        value_1.bits[2] -= 1;
      }
      value_1.bits[1] -= 1;
    }
  }
  //    if (value_2.bits[0] < value_2.bits[0]) value_3.bits[1] -= 1;
  for (int i = 0; i <= 95; i++) {
    if ((get_bit(value_1, i) == 1) && (get_bit(value_2, i) == 1)) {
      if (temp == 1)
        setBit(i, &result);
      else
        temp = 1;
    }
    if (get_bit(value_1, i) ^ (get_bit(value_2, i))) {
      if (temp == 0) setBit(i, &result);
    }
    if ((get_bit(value_1, i) == 0) && (get_bit(value_2, i) == 0)) {
      if (temp == 1) {
        setBit(i, &result);
        temp = 0;
      }
    }
    if (((i == 31) || (i == 63) || (i == 95)) && (subFlag == 1)) temp = 0;
    if (i == 95)
      if (overflow_check(get_bit(value_1, i), get_bit(value_2, i), temp) == 1)
        break;  // make result inf or nan or smth?
  }
  return result;
}

int overflow_check(int bit1, int bit2, int temp) {
  int error = 0;
  if ((bit1 + bit2 + temp) > 1) {
    error = 1;
  }
  return error;
}

int overflow_check_big(s21_decimal_big value) {
  int overflow = 0;

  for (int i = 96; i <= 223; i++) {
    if (get_bit_big(value, i) == 1) {
      overflow = 1;
      break;
    }
  }
  return overflow;
}

int big_rounding(s21_decimal_big *value) {
  s21_decimal_big ten_mul = {{10, 0, 0, 0, 0, 0, 0, 1 << 16}},
                  ten = {{10, 0, 0, 0, 0, 0, 0, 0}},
                  one = {{1, 0, 0, 0, 0, 0, 0, 0}},
                  five = {{5, 0, 0, 0, 0, 0, 0, 1 << 16}}, res = {{0}},
                  remainder = {{0}};
  int exp = getExp(value->bits[7]), sign = value->bits[7] >> 31, error = 0;
  value->bits[7] = ((value->bits[7] << 1) >> 1);
  for (int i = 0; i < exp - 1; i++) s21_mul_big(ten_mul, ten, &ten_mul);
  s21_div_big_ten(*value, ten_mul, &res, &remainder);
  unsigned int temp = res.bits[7];
  res.bits[7] = remainder.bits[7];
  remainder.bits[7] = temp;
  if (s21_is_greater_or_equal_big(remainder, five) == 1) {
    *value = add_function_big(res, one, 0);
    if (overflow_check_big(*value) == 1) {
      *value = sub_function_big(*value, one);
    }
  } else {
    *value = res;
  }
  if (sign == 1) value->bits[7] = 1 << 31;
  return error;
}

// if (overflowFix == 0) -> fixed, else ( == 1) cant fix
int overflowFix(s21_decimal_big *value) {
  int exp = getExp(value->bits[7]), overflow = 0,
      sign = value->bits[7] = value->bits[7] >> 31;
  value->bits[7] = ((value->bits[7] << 1) >> 1);
  while ((overflow_check_big(*value) == 1) && (exp != 0)) {
    value->bits[7] = 1 << 16;
    big_rounding(value);
    exp--;
    value->bits[7] = exp << 16;
  }
  if (sign == 1) value->bits[7] = (1 << 31) + (exp << 16);
  if (overflow_check_big(*value) == 1) overflow = 1;
  return overflow;
}

// if (overflowFix == 0) -> fixed, else ( == 1) cant fix
/*int overflowFix(s21_decimal_big *value) {
  s21_decimal_big ten = {{10, 0, 0, 0, 0, 0, 0, 1 << 16}}, remainder = {{0}};
  int overflow = 0, exp = getExp(value->bits[7]);
  while ((overflow_check_big(*value) == 1) && exp != 0) {
    s21_div_big_ten(*value, ten, value, &remainder);
    exp = getExp(value->bits[7]);
  }
  if (overflow_check_big(*value) == 1) {
    overflow = 1;
  }
  return overflow;
}*/

int normalize(s21_decimal *value_1, s21_decimal *value_2) {
  int exp_1 = getExp(value_1->bits[3]), exp_2 = getExp(value_2->bits[3]),
      error = 0;
  if ((exp_1 > 28) || (exp_2 > 28)) {
    error = 2;
  } else {
    s21_decimal_big val_1 = convertBig(*value_1), val_2 = convertBig(*value_2),
                    ten = {{10, 0, 0, 0, 0, 0, 0, 1 << 16}}, remainder = {{0}};
    if (exp_1 > exp_2) {
      for (int i = 0; i < (exp_1 - exp_2); i++) {
        if (s21_mul_big(val_2, ten, &val_2) != 0) error = 2;
      }
      exp_2 = getExp(val_2.bits[7]);
      if (exp_2 != exp_1) {
        for (int i = 0; i < (exp_1 - exp_2); i++) {
          if (s21_div_big_ten(val_1, ten, &val_1, &remainder) != 0) error = 2;
        }
      }
      *value_1 = convertBack(val_1);
      *value_2 = convertBack(val_2);
    } else if (exp_2 > exp_1) {
      for (int i = 0; i < (exp_2 - exp_1); i++) {
        if (s21_mul_big(val_1, ten, &val_1) != 0) error = 2;
      }
      exp_1 = getExp(val_1.bits[7]);
      if (exp_1 != exp_2) {
        for (int i = 0; i < (exp_2 - exp_1); i++) {
          if (s21_div_big_ten(val_2, ten, &val_2, &remainder) != 0) error = 2;
        }
      }
      *value_1 = convertBack(val_1);
      *value_2 = convertBack(val_2);
    }
  }
  return error;
}

s21_decimal sub_function(s21_decimal value_1, s21_decimal value_2) {
  s21_decimal result = {{0, 0, 0, value_1.bits[3]}};
  for (int i = 0; i <= 95; i++) {
    if ((get_bit(value_1, i) == 1) && (get_bit(value_2, i) == 1)) {
      removeBit(i, &result);
    } else if ((get_bit(value_1, i) == 1) && (get_bit(value_2, i) == 0)) {
      setBit(i, &result);
    } else if ((get_bit(value_1, i) == 0) && (get_bit(value_2, i) == 1)) {
      int iter = i + 1;
      for (int z = iter; z < 95; z++) {
        if (get_bit(value_1, z) == 0) {
          iter++;
        } else if (get_bit(value_1, z) == 1) {
          removeBit(z, &value_1);
          break;
        }
      }
      for (int n = i + 1; n < iter; n++) {
        setBit(n, &value_1);
      }
      setBit(i, &result);
    } else if ((get_bit(value_1, i) == 0) && (get_bit(value_2, i) == 0)) {
      removeBit(i, &result);
    }
    // overflow_check !!
  }
  return result;
}

s21_decimal signLogic(int value_1_sign, int value_2_sign, s21_decimal value_1,
                      s21_decimal value_2, int test) {
  s21_decimal result = {{0, 0, 0, 0}};
  if (value_1_sign == 0 && value_2_sign == 0) {
    result = sub_function(value_1, value_2);
    if (test == 2) {
      setSignInt(1, &result);
    }
  } else if (value_1_sign == 1 && value_2_sign == 0) {
    setSignInt(0, &value_1);
    result = add_function(value_1, value_2, 0);
    setSignInt(1, &result);
  } else if (value_1_sign == 0 && value_2_sign == 1) {
    setSignInt(0, &value_2);
    result = add_function(value_1, value_2, 0);
    setSignInt(0, &result);
  } else if (value_1_sign == 1 && value_2_sign == 1) {
    setSignInt(0, &value_1);
    setSignInt(0, &value_2);
    if (test == 2) {
      result = add_function(value_1, value_2, 0);
      setSignInt(1, &result);
    } else {
      result = sub_function(value_1, value_2);
    }
  }
  return result;
}

s21_decimal divLogic(s21_decimal value_1, s21_decimal value_2,
                     s21_decimal *remainder_val) {
  s21_decimal res = {{0, 0, 0, 0}};

  while (s21_is_greater_or_equal(value_1, value_2)) {
    s21_decimal temp_val2 = value_2;
    int j = 0, last_j = 0;
    while (s21_is_greater(value_1, temp_val2)) {
      temp_val2 = value_2;
      last_j = j++;
      temp_val2 = setShift(temp_val2, j);
    }

    if (last_j > 0) {
      s21_decimal mod1 = {{2, 0, 0, 0}};
      s21_decimal mod2 = {{2, 0, 0, 0}};
      for (int i = 0; i < last_j - 1; i++) {
        s21_mul(mod1, mod2, &mod1);
      }
      s21_add(res, mod1, &res);
    } else if (last_j == 0) {
      s21_decimal one = {{1, 0, 0, 0}};
      s21_add(res, one, &res);
    }
    temp_val2 = value_2;
    temp_val2 = setShift(temp_val2, last_j);
    s21_sub(value_1, temp_val2, &value_1);
  }

  *remainder_val = value_1;
  return res;
}

int isZero(s21_decimal value_1) {
  int res = 1;
  for (int i = 0; i < 3; i++)
    if (value_1.bits[i] != 0) res = 0;
  return res;
}

s21_decimal s21_div_part(s21_decimal value_1, s21_decimal value_2,
                         s21_decimal *result) {
  //ПРОВЕРИТЬ ПЕРЕПОЛНЕНИЕ
  s21_decimal res = {{0, 0, 0, 0}}, remainder_val = {{0}};
  if (value_2.bits[0] != 0 || value_2.bits[1] != 0 || value_2.bits[2] == 0) {
    if (s21_is_greater(value_1, value_2)) {
      res = divLogic(value_1, value_2, &remainder_val);
    } else if (s21_is_equal(value_1, value_2)) {
      res.bits[0] = 1;
    }  // VAL1 < VAL2
  }
  *result = res;
  return remainder_val;
}
