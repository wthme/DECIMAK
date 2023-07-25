#include "s21_decimal.h"

void get_bits_big(s21_decimal_big obj) {
  for (int i = 0; i <= 223; i++) {
    printf("%d", get_bit_big(obj, i));
  }
}

void set_bit_big(s21_decimal_big *dst, int index) {
  // int error = 0;  // unused variable
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
  else if ((index >= 128) && (index <= 159))
    dst->bits[4] |= bit;
  else if ((index >= 160) && (index <= 191))
    dst->bits[5] |= bit;
  else if ((index >= 192) && (index <= 223))
    dst->bits[6] |= bit;
  // else
  // error = 1;
  // return error;
}

void removeBit_big(int j, s21_decimal_big *dst) {
  dst->bits[j / 32] &= ~(1 << (j % 32));
}

void setSignIntBig(int sign, s21_decimal_big *dst) {
  if (sign == 1) {
    dst->bits[7] |= MINUS;
  } else if (sign == 0) {
    dst->bits[7] &= PLUS;
  }
}

int nonZeroNumberBig(s21_decimal_big dst) {
  int flag_check = 0;
  for (int i = 0; i < 7; i++) {
    if (dst.bits[i] > 0) {
      flag_check = 1;
    }
  }
  return flag_check;
}

int get_bit_big(s21_decimal_big value, int i) {
  unsigned int mask = 1u << (i % 32);  // 1u - это unsigned int 1
  return (!!(value.bits[i / 32] & mask));
}

s21_decimal_big convertBig(s21_decimal dst) {
  s21_decimal_big res = {{0, 0, 0, 0, 0, 0, 0, 0}};
  for (int i = 0; i < 3; i++) {
    res.bits[i] = dst.bits[i];
  }
  res.bits[7] = dst.bits[3];
  return res;
}

s21_decimal convertBack(s21_decimal_big dst) {
  s21_decimal res = {{0, 0, 0, 0}};
  for (int i = 0; i < 3; i++) {
    res.bits[i] = dst.bits[i];
  }
  res.bits[3] = dst.bits[7];
  return res;
}

s21_decimal_big add_function_big(s21_decimal_big value_1,
                                 s21_decimal_big value_2, int subFlag) {
  int temp = 0;
  s21_decimal_big result = {{0, 0, 0, 0, 0, 0, 0, value_1.bits[7]}};
  if (subFlag == 1) {
    if (value_1.bits[0] < value_2.bits[0]) {
      if (value_1.bits[1] == 0) {
        value_1.bits[2] -= 1;
      }
      value_1.bits[1] -= 1;
    }
  }
  //    if (value_2.bits[0] < value_2.bits[0]) value_3.bits[1] -= 1;
  for (int i = 0; i <= 223; i++) {
    if ((get_bit_big(value_1, i) == 1) && (get_bit_big(value_2, i) == 1)) {
      if (temp == 1)
        set_bit_big(&result, i);
      else
        temp = 1;
    }
    if (get_bit_big(value_1, i) ^ (get_bit_big(value_2, i))) {
      if (temp == 0) set_bit_big(&result, i);
    }
    if ((get_bit_big(value_1, i) == 0) && (get_bit_big(value_2, i) == 0)) {
      if (temp == 1) {
        set_bit_big(&result, i);
        temp = 0;
      }
    }
    if (((i == 31) || (i == 63) || (i == 95) || (i == 127) || (i == 159) ||
         (i == 191) || (i == 223)) &&
        (subFlag == 1))
      temp = 0;
    if (i == 223)
      if (overflow_check(get_bit_big(value_1, i), get_bit_big(value_2, i),
                         temp) == 1)
        break;  // make result inf or nan or smth?
  }
  return result;
}

void add_sign_chek(int value_1_sign, int value_2_sign, s21_decimal_big value_1,
                   s21_decimal_big value_2, s21_decimal_big *res_bit) {
  if (value_1_sign == 0 && value_2_sign == 0) {
    res_bit->bits[7] &= PLUS;
  } else if (value_1_sign == 1 && value_2_sign == 1) {
    res_bit->bits[7] |= MINUS;
  } else if (value_1_sign == 1 && value_2_sign == 0) {
    res_bit->bits[7] &= PLUS;
    if (s21_is_greater_big(value_1, value_2)) {
      res_bit->bits[7] |= MINUS;
    }
  } else if (value_1_sign == 0 && value_2_sign == 1) {
    res_bit->bits[7] |= MINUS;
    if (s21_is_greater_or_equal_big(value_1, value_2)) {
      res_bit->bits[7] &= PLUS;
    }
  }
}

int s21_is_greater_big(s21_decimal_big value_1, s21_decimal_big value_2) {
  int sign_1 = getSignInt(value_1.bits[7]),
      sign_2 = getSignInt(value_2.bits[7]),
      error = normalize_big(&value_1, &value_2);
  int res = 0;

  if ((sign_1 == 0) && (sign_2 == 1))
    res = 1;
  else if ((sign_1 == 1) && (sign_2 == 0))
    res = 0;
  else {
    for (int i = 223; i >= 0; i--) {
      if ((get_bit_big(value_1, i) == 1) && (get_bit_big(value_2, i) == 1))
        continue;
      else if ((get_bit_big(value_1, i) == 1) &&
               (get_bit_big(value_2, i) == 0)) {
        res = 1;
        break;
      } else if ((get_bit_big(value_1, i) == 0) &&
                 (get_bit_big(value_2, i) == 1)) {
        res = 0;
        break;
      }
    }
  }
  if ((sign_1 == 1) && (sign_2 == 1)) res = !res;
  if (error != 0) error = error;
  return res;
}

int s21_is_equal_big(s21_decimal_big value_1, s21_decimal_big value_2) {
  int res = 1, sign_1 = getSignInt(value_1.bits[7]),
      sign_2 = getSignInt(value_2.bits[7]),
      error = normalize_big(&value_1, &value_2);
  if (error != 0) error = error;
  if ((sign_1 ^ sign_2) == 0) {
    if (getExp(value_1.bits[7]) == getExp(value_2.bits[7])) {
      for (int i = 223; i >= 0; i--) {
        if (get_bit_big(value_1, i) != get_bit_big(value_2, i)) {
          res = 0;
          break;
        }
      }
    } else
      res = 0;
  } else
    res = 0;
  return res;
}

int s21_is_greater_or_equal_big(s21_decimal_big value_1,
                                s21_decimal_big value_2) {
  return (s21_is_greater_big(value_1, value_2) ||
          (s21_is_equal_big(value_1, value_2)));
}

s21_decimal_big setShiftBig(s21_decimal_big dst, int j) {
  for (int i = 0; i < j; i++) {
    dst.bits[6] = dst.bits[6] << 1;
    int counter = 191;
    for (int t = 5; t >= 0; t--) {
      if (get_bit_big(dst, counter) == 1) {
        set_bit_big(&dst, counter + 1);
        dst.bits[t] = dst.bits[t] << 1;
      } else
        dst.bits[t] = dst.bits[t] << 1;
      counter -= 32;
    }
  }
  return dst;
}

int s21_is_less_big(s21_decimal_big value_1, s21_decimal_big value_2) {
  int sign_1 = getSignInt(value_1.bits[7]),
      sign_2 = getSignInt(value_2.bits[7]);
  int res = 0, error = normalize_big(&value_1, &value_2);
  if (error != 0) error = error;
  if ((sign_1 == 1) && (sign_2 == 0))
    res = 1;
  else if ((sign_1 == 0) && (sign_2 == 1))
    res = 0;
  else {
    for (int i = 223; i >= 0; i--) {
      if ((get_bit_big(value_1, i) == 1) && (get_bit_big(value_2, i) == 1))
        continue;
      else if ((get_bit_big(value_1, i) == 1) &&
               (get_bit_big(value_2, i) == 0)) {
        res = 0;
        break;
      } else if ((get_bit_big(value_2, i) == 1) &&
                 (get_bit_big(value_1, i) == 0)) {
        res = 1;
        break;
      }
    }

    if ((sign_1 == 1) && (sign_2 == 1)) res = !res;
  }
  return res;
}

s21_decimal_big sub_function_big(s21_decimal_big value_1,
                                 s21_decimal_big value_2) {
  s21_decimal_big result = {{0, 0, 0, 0, 0, 0, 0, value_1.bits[7]}};
  for (int i = 0; i <= 223; i++) {
    if ((get_bit_big(value_1, i) == 1) && (get_bit_big(value_2, i) == 1)) {
      removeBit_big(i, &result);
    } else if ((get_bit_big(value_1, i) == 1) &&
               (get_bit_big(value_2, i) == 0)) {
      set_bit_big(&result, i);
    } else if ((get_bit_big(value_1, i) == 0) &&
               (get_bit_big(value_2, i) == 1)) {
      int iter = i + 1;
      for (int z = iter; z <= 223; z++) {
        if (get_bit_big(value_1, z) == 0) {
          iter++;
        } else if (get_bit_big(value_1, z) == 1) {
          removeBit_big(z, &value_1);
          break;
        }
      }
      for (int n = i + 1; n < iter; n++) {
        set_bit_big(&value_1, n);
      }
      set_bit_big(&result, i);
    } else if ((get_bit_big(value_1, i) == 0) &&
               (get_bit_big(value_2, i) == 0)) {
      removeBit_big(i, &result);
    }
    // overflow_check !!
  }

  // printf("\n\n %u \n\n", value_1_big.bits[6]);

  return result;
}

void sub_sign_chek(int value_1_sign, int value_2_sign, int test,
                   s21_decimal_big value_1, s21_decimal_big value_2,
                   s21_decimal_big *result) {
  if (value_1_sign == 1 && value_2_sign == 1) {
    result->bits[7] &= PLUS;
    if (s21_is_greater_or_equal_big(value_1, value_2) && test != 3) {
      result->bits[7] |= MINUS;
    }
  } else if (value_1_sign == 1 && value_2_sign == 0) {
    result->bits[7] |= MINUS;
  } else if (value_2_sign == 1 && value_1_sign == 0) {
    result->bits[7] &= PLUS;
  } else if (value_2_sign == 0 && value_1_sign == 0) {
    result->bits[7] |= MINUS;
    if (s21_is_greater_big(value_1, value_2) && test != 2) {
      result->bits[7] &= PLUS;
    }
  }
}

s21_decimal_big signLogicBig(int value_1_sign, int value_2_sign,
                             s21_decimal_big value_1, s21_decimal_big value_2,
                             int test) {
  s21_decimal_big result = {{0, 0, 0, 0, 0, 0, 0, value_1.bits[7]}};

  if (value_1_sign == 0 && value_2_sign == 0) {
    result = sub_function_big(value_1, value_2);
  } else if (value_1_sign == 1 && value_2_sign == 0) {
    s21_add_big(value_1, value_2, &result);
  } else if (value_1_sign == 0 && value_2_sign == 1) {
    s21_add_big(value_1, value_2, &result);
  } else if (value_1_sign == 1 && value_2_sign == 1) {
    if (test == 2) {
      s21_add_big(value_1, value_2, &result);
    } else {
      result = sub_function_big(value_1, value_2);
    }
  }
  return result;
}

s21_decimal_big divLogicBig(s21_decimal_big value_1, s21_decimal_big value_2,
                            s21_decimal_big *remainder_val) {
  s21_decimal_big res = {0};

  while (s21_is_greater_or_equal_big(value_1, value_2)) {
    s21_decimal_big temp_val2 = value_2;
    int j = 0, last_j = 0;
    while (s21_is_greater_or_equal_big(value_1, temp_val2)) {
      temp_val2 = value_2;
      last_j = j++;
      temp_val2 = setShiftBig(temp_val2, j);
    }

    if (last_j > 0) {
      s21_decimal_big mod1 = {{2, 0, 0, 0, 0, 0, 0, 0}};
      s21_decimal_big mod2 = {{2, 0, 0, 0, 0, 0, 0, 0}};
      for (int i = 0; i < last_j - 1; i++) {
        s21_mul_big(mod1, mod2, &mod1);
      }
      s21_add_big(res, mod1, &res);
    } else if (last_j == 0) {
      s21_decimal_big one = {{1, 0, 0, 0, 0, 0, 0, 0}};
      s21_add_big(res, one, &res);
    }
    temp_val2 = value_2;
    temp_val2 = setShiftBig(temp_val2, last_j);
    s21_sub_big(value_1, temp_val2, &value_1);
  }

  *remainder_val = value_1;
  return res;
}

void remainder_def(int result_exp, s21_decimal_big remainder_val,
                   s21_decimal_big value_2, s21_decimal_big *res_big) {
  int flag_test = 1;
  int count_ten = result_exp;
  while (flag_test == 1 && count_ten < 28) {
    flag_test = 0;
    for (int i = 0; i < 6; i++) {
      if (remainder_val.bits[i] > 0) {
        flag_test = 1;
      }
    }

    if (flag_test == 1) {
      s21_decimal_big ten = {{10, 0, 0, 0, 0, 0, 0, 0}};
      while (s21_is_greater_big(remainder_val, value_2) != 1 &&
             count_ten < 28) {
        count_ten++;
        s21_mul_big(remainder_val, ten, &remainder_val);
        s21_mul_big(*res_big, ten, res_big);
      }
      s21_decimal_big res_big_dop = {0};
      s21_div_big_ten(remainder_val, value_2, &res_big_dop, &remainder_val);
      s21_add_big(*res_big, res_big_dop, res_big);
    }
  }

  res_big->bits[7] = (count_ten << 16);
}

int s21_div_big_ten(s21_decimal_big value_1, s21_decimal_big value_2,
                    s21_decimal_big *result, s21_decimal_big *remainder) {
  s21_decimal_big res_big = {0};
  s21_decimal_big remainder_val = res_big;

  int value_1_exp = getExp(value_1.bits[7]),
      value_2_exp = getExp(value_2.bits[7]);

  int result_exp = value_1_exp - value_2_exp;

  if (result_exp < 0) result_exp *= -1;

  value_1.bits[7] = 0;
  value_2.bits[7] = 0;

  setSignIntBig(0, &value_1);  // !!!
  setSignIntBig(0, &value_2);  // !!!

  if (nonZeroNumberBig(value_1)) {
    if (s21_is_greater_big(value_1, value_2)) {
      res_big = divLogicBig(value_1, value_2, &remainder_val);
    } else if (s21_is_equal_big(value_1, value_2)) {
      res_big.bits[0] = 1;
    }  // VAL1 < VAL2
  }
  *remainder = remainder_val;

  *result = res_big;
  result->bits[7] = (result_exp << 16);  //
  return 0;
}

int normalize_big(s21_decimal_big *value_1, s21_decimal_big *value_2) {
  int exp_1 = getExp(value_1->bits[7]), exp_2 = getExp(value_2->bits[7]),
      error = 0;
  s21_decimal_big ten = {{10, 0, 0, 0, 0, 0, 0, 1 << 16}}, remainder = {{0}},
                  mul_ten = {{10, 0, 0, 0, 0, 0, 0, 1 << 16}};
  if ((exp_1 > 28) || (exp_2 > 28)) {
    error = 2;
  } else {
    if (exp_1 > exp_2) {
      for (int i = 0; i < (exp_1 - exp_2 - 1); i++) {
        s21_mul_big(mul_ten, ten, &mul_ten);
      }
      s21_mul_big(*value_2, mul_ten, value_2);
      exp_2 = getExp(value_2->bits[7]);
      if (exp_2 != exp_1) {
        for (int i = 0; i < (exp_1 - exp_2); i++)
          s21_div_big_ten(*value_1, ten, value_1, &remainder);
      }
    } else if (exp_2 > exp_1) {
      for (int i = 0; i < (exp_2 - exp_1 - 1); i++) {
        s21_mul_big(mul_ten, ten, &mul_ten);
      }
      s21_mul_big(*value_1, mul_ten, value_1);
      exp_1 = getExp(value_1->bits[7]);
      if (exp_1 != exp_2) {
        for (int i = 0; i < (exp_2 - exp_1); i++)
          s21_div_big_ten(*value_2, ten, value_2, &remainder);
      }
    }
  }
  return error;
}
