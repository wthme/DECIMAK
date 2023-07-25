#include <math.h>
#include <stdio.h>
#define MINUS 0x80000000

typedef struct {
  unsigned int bits[4];
} s21_decimal;

int getScale(float src);
int getExp(int bit3);
int setBit(int index, s21_decimal *dst);
int getSignInt(int src);
void setSignInt(int sign, s21_decimal *dst);
int s21_from_int_to_decimal(int src, s21_decimal *dst);
int s21_from_float_to_decimal(float src, s21_decimal *dst);
int s21_from_decimal_to_int(s21_decimal src, int *dst);
int s21_from_decimal_to_float(s21_decimal src, float *dst);
int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int get_bit(s21_decimal value, int i);
// s21_decimal normalize(s21_decimal value, int exp);
s21_decimal add_function(s21_decimal value_1, s21_decimal value_2, int subFlag);
int overflow_check(int bit1, int bit2, int temp);
int normalize(s21_decimal *value_1, s21_decimal *value_2);
int s21_is_less(s21_decimal value_1, s21_decimal value_2);
int s21_is_greater(s21_decimal value_1, s21_decimal value_2);
int s21_is_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_less_or_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_greater_or_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_not_equal(s21_decimal value_1, s21_decimal value_2);
// s21_decimal add_function_sub(s21_decimal value_1, s21_decimal value_2);

int main() {
  s21_decimal temp = {0};
  int x = 1234567;
  s21_from_int_to_decimal(x, &temp);
  x = -7654321;
  s21_decimal temp1 = {0};
  s21_from_int_to_decimal(x, &temp1);
  s21_decimal temp2 = {0};
  float y = 0.456;
  s21_from_float_to_decimal(y, &temp2);
  y = -654.321;
  s21_decimal temp3 = {0};
  s21_from_float_to_decimal(y, &temp3);
  s21_decimal temp4 = {{189123, 0, 0, 2147483648}};  // 196608 - scale = 3;
  int result = 0;
  s21_from_decimal_to_int(temp4, &result);
  // printf("%d\n", result);
  float floatresult = 0;
  s21_decimal temp5 = {{12345, 0, 0, 196608}};
  s21_from_decimal_to_float(temp5, &floatresult);
  // printf("%f\n", floatresult);
  s21_decimal add1 = {{123, 0, 3, 2147483648}};
  s21_decimal add2 = {{421, 0, 0, 0}};
  s21_decimal res = {0};
  s21_add(add1, add2, &res);
  printf("______add______\n");
  for (int i = 0; i <= 3; i++) printf("%u\t", res.bits[i]);
  printf("\n");
  s21_decimal sub1 = {{421, 1000, 55, 0}};
  s21_decimal sub2 = {{123, 1, 18, 0}};
  s21_decimal sub_res = {0};
  s21_sub(sub1, sub2, &sub_res);
  printf("______sub______\n");
  for (int i = 0; i <= 3; i++) printf("%u\t", sub_res.bits[i]);
  s21_decimal less_1 = {{4210, 0, 0, 0}};
  s21_decimal less_2 = {{1230, 0, 0, 0}};
  printf("\n______less_____\n");
  int less = s21_is_less(less_1, less_2);
  printf("%d\n", less);
  s21_decimal less_11 = {{4210, 0, 0, 2147483648}};
  s21_decimal less_22 = {{1230, 0, 0, 2147483648}};
  int less2 = s21_is_less(less_11, less_22);
  printf("%d\n", less2);
  s21_decimal great1 = {{4210, 0, 0, 0}};
  s21_decimal great2 = {{1230, 0, 0, 0}};
  printf("___greater____\n");
  int great = s21_is_greater(great1, great2);
  printf("%d\n", great);
  s21_decimal great11 = {{4210, 0, 0, 2147483648}};
  s21_decimal great22 = {{12300, 0, 0, 2147483648}};
  int gr2 = s21_is_greater(great11, great22);
  printf("%d\n", gr2);
  printf("______eq______\n");
  s21_decimal eq1 = {{123, 345, 567, 2147483648}};
  s21_decimal eq2 = {{123, 345, 567, 2147483648}};
  int eq = s21_is_equal(eq1, eq2);
  printf("%d\n", eq);
  printf("___lessOrEq____\n");
  printf("%d\n%d\n%d\n", s21_is_less_or_equal(eq1, eq2),
         s21_is_less_or_equal(great22, great11),
         s21_is_less_or_equal(great1, great2));
  printf("__greaterOrEq__\n");
  printf("%d\n%d\n%d\n", s21_is_greater_or_equal(eq1, eq2),
         s21_is_greater_or_equal(great22, great11),
         s21_is_greater_or_equal(great1, great2));
  printf("_____notEq_____\n");
  printf("%d\n%d\n", s21_is_not_equal(eq1, eq2),
         s21_is_not_equal(great1, great2));

  return 0;
}

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  setSignInt(getSignInt(src), dst);
  int mask = 0xFFFFFFFF;
  dst->bits[0] = src & mask;
  // printf("%u\t%d\n", dst->bits[3], dst->bits[0]);
  return 0;
}

int getSignInt(int src) {
  int sign = 0;
  sign = -1 * (src >> 31);
  return sign;
}

void setSignInt(int sign, s21_decimal *dst) {
  if (sign == 1) dst->bits[3] = MINUS;
}

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  int scale = getScale(src);
  if (src < 0) {
    src = -src;
    dst->bits[3] = MINUS;
  }
  src = src * pow(10, scale);
  long long unsigned int newFloat = src;
  dst->bits[3] |= (scale << 16);
  for (int i = 95; i >= 0; i--) {
    if (newFloat >= pow(2, i)) {
      setBit(i, dst);
      newFloat = newFloat - pow(2, i);
    }
  }
  // for (int i = 3; i >= 0; i--) printf("%u\t", dst->bits[i]);
  // printf("\n");
  return 0;
}

int setBit(int index, s21_decimal *dst) {
  int error = 0;
  long long unsigned int bit = pow(2, index % 32);
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

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  int exp = getExp(src.bits[3]);
  // for (int i = 3; i >= 0; i--) printf("%u\t", src.bits[i]);
  // printf("\n");
  for (int i = 2; i >= 0; i--) {
    for (int j = 31; j >= 0; j--) {
      if (((src.bits[i] >> j) & 1) == 1) {
        *dst = *dst + pow(2, (i + 1) * j);
      }
    }
  }
  *dst = *dst / pow(10, exp);
  if (((src.bits[3] >> 31) && 1) == 1) *dst = -*dst;
  return 0;
}

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  int exp = getExp(src.bits[3]);
  // for (int i = 3; i >= 0; i--) printf("%u\t", src.bits[i]);
  // printf("\n");
  for (int i = 2; i >= 0; i--) {
    for (int j = 31; j >= 0; j--) {
      if (((src.bits[i] >> j) & 1) == 1) {
        *dst = *dst + pow(2, (i + 1) * j);
      }
    }
  }
  *dst = *dst / pow(10, exp);
  if (((src.bits[3] >> 31) && 1) == 1) *dst = -*dst;
  return 0;
}

int getExp(int bit3) {
  int exp = 0xFF;
  bit3 = bit3 >> 16;
  exp = exp & bit3;
  return exp;
}

/*int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int exp_1 = getExp(value_1.bits[3]), exp_2 = getExp(value_2.bits[3]),
      error = 0;
  if ((exp_1 > 28) || (exp_2 > 28))
    error = 2;  // NINF?
  else {
    if (exp_1 > exp_2)
      value_2 = normalize(value_2, exp_1 - exp_2);
    else if (exp_1 < exp_2)
      value_1 = normalize(value_1, exp_2 - exp_1);
    *result = add_function(value_1, value_2);
  }
  return error;
}*/

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int resultSign = 0, value_1_sign = getSignInt(value_1.bits[3]),
      value_2_sign = getSignInt(value_2.bits[3]),
      error = normalize(&value_1, &value_2);
  if (error != 2) {
    if (s21_is_greater(value_1, value_2))
      resultSign = value_1_sign;
    else
      resultSign = value_2_sign;
    if ((value_1_sign ^ value_2_sign) == 0)
      *result = add_function(value_1, value_2, 0);
    else if (s21_is_greater(value_1, value_2))
      s21_sub(value_1, value_2, result);
    else
      s21_sub(value_2, value_1, result);
    if (resultSign == 1) setBit(127, result);
  }
  return error;
}

// s21_add(-3, 5) = s21_sub(5, 3) s21_sub(sign = 0, sign = 1)

int get_bit(s21_decimal value, int i) {
  unsigned int mask = 1u << (i % 32);  // 1u - это unsigned int 1
  return (!!(value.bits[i / 32] & mask));
}

/*s21_decimal add_function(s21_decimal value_1, s21_decimal value_2) {
  int temp = 0;
  s21_decimal result = {0, 0, 0, value_1.bits[3]};
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
    if (i == 95)
      if (overflow_check(get_bit(value_1, i), get_bit(value_2, i), temp) == 1)
        break;  // make result inf or nan or smth?
  }
  return result;
}*/

/*s21_decimal normalize(s21_decimal value, int exp) {
  s21_decimal result = {0};
  for (int i = 0; i < pow(10, exp); i++) {
    result = add_function(value, result);
  }
  return result;
}*/

int normalize(s21_decimal *value_1, s21_decimal *value_2) {
  int exp_1 = getExp(value_1->bits[3]), exp_2 = getExp(value_2->bits[3]),
      error = 0, mask = 0xFF0000;
  value_1->bits[3] &= mask;
  value_2->bits[3] &= mask;
  // printf("\n\n%d\t%d\n\n\n", exp_1, exp_2);
  s21_decimal result = {0};
  if ((exp_1 > 28) || (exp_2 > 28))
    error = 2;
  else {
    if (exp_1 > exp_2) {
      for (int i = 0; i < pow(10, exp_1); i++) {
        result = add_function(*value_2, result, 0);
      }
      *value_2 = result;
      value_2->bits[3] = value_1->bits[3];  // deal with sign now
    } else if (exp_2 > exp_1) {
      result.bits[3] = value_2->bits[3];
      for (int i = 0; i < pow(10, exp_2); i++) {
        result = add_function(*value_1, result, 0);
      }
      *value_1 = result;
      value_1->bits[3] = value_2->bits[3];  // or later?
    }
  }
  return error;
}

int overflow_check(int bit1, int bit2, int temp) {
  int error = 0;
  if ((bit1 + bit2 + temp) > 1) {
    printf("OVERFLOW\n");
    error = 1;
  }
  return error;
}
// figure out result sign + add/sub if (subFlag (maybe?))
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int value_1_sign = getSignInt(value_1.bits[3]),
      value_2_sign = (!(getSignInt(value_2.bits[3])));
  if (value_1_sign ^ value_2_sign) {
    if (value_1_sign > value_2_sign) {
      for (int i = 0; i <= 2; i++) value_1.bits[i] = ~value_1.bits[i] + 1;
    } else if (value_2_sign > value_1_sign)
      for (int i = 0; i <= 2; i++) value_2.bits[i] = ~value_2.bits[i] + 1;
  }
  int error = normalize(&value_1, &value_2);
  if (error != 2) {
    *result = add_function(value_1, value_2, 1);
  }
  return 0;
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

// check sign first
int s21_is_less(s21_decimal value_1, s21_decimal value_2) {
  int error = normalize(&value_1, &value_2), res = 0;
  if (error != 2) {
    if ((getSignInt(value_1.bits[3]) == 1) &&
        (getSignInt(value_2.bits[3]) == 0))
      res = 1;
    else if ((getSignInt(value_1.bits[3]) == 0) &&
             (getSignInt(value_2.bits[3]) == 1))
      res = 0;
    else {
      for (int i = 95; i >= 0; i--) {
        if ((get_bit(value_1, i) == 1) && (get_bit(value_2, i) == 1))
          continue;
        else if ((get_bit(value_1, i) == 1) && (get_bit(value_2, i) == 0)) {
          res = 0;
          break;
        } else if ((get_bit(value_2, i) == 1) && (get_bit(value_1, i) == 0)) {
          res = 1;
          break;
        }
      }
    }
    if ((getSignInt(value_1.bits[3]) == 1) &&
        (getSignInt(value_2.bits[3]) == 1))
      res = !res;
  }
  return res;
}

int s21_is_greater(s21_decimal value_1, s21_decimal value_2) {
  int error = normalize(&value_1, &value_2), res = 0;
  if (error != 2) {
    if ((getSignInt(value_1.bits[3]) == 0) &&
        (getSignInt(value_2.bits[3]) == 1))
      res = 1;
    else if ((getSignInt(value_1.bits[3]) == 1) &&
             (getSignInt(value_2.bits[3]) == 0))
      res = 0;
    else {
      for (int i = 95; i >= 0; i--) {
        if ((get_bit(value_1, i) == 1) && (get_bit(value_2, i) == 1))
          continue;
        else if ((get_bit(value_1, i) == 1) && (get_bit(value_2, i) == 0)) {
          res = 1;
          break;
        } else if ((get_bit(value_1, i) == 0) && (get_bit(value_2, i) == 1)) {
          res = 0;
          break;
        }
      }
    }
    if ((getSignInt(value_1.bits[3]) == 1) &&
        (getSignInt(value_2.bits[3]) == 1))
      res = !res;
  }
  return res;
}
// add normalize below
int s21_is_equal(s21_decimal value_1, s21_decimal value_2) {
  int res = 1;
  if ((getSignInt(value_1.bits[3]) ^ getSignInt(value_2.bits[3])) == 0) {
    if (getExp(value_1.bits[3]) == getExp(value_2.bits[3])) {
      for (int i = 95; i >= 0; i--) {
        if (get_bit(value_1, i) != get_bit(value_2, i)) {
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

int s21_is_less_or_equal(s21_decimal value_1, s21_decimal value_2) {
  return (s21_is_less(value_1, value_2) || (s21_is_equal(value_1, value_2)));
}

int s21_is_greater_or_equal(s21_decimal value_1, s21_decimal value_2) {
  return (s21_is_greater(value_1, value_2) || (s21_is_equal(value_1, value_2)));
}

int s21_is_not_equal(s21_decimal value_1, s21_decimal value_2) {
  return (!(s21_is_equal(value_1, value_2)));
}
// check for overflow //kinda done
// downscale second value if i can't scale first one (overflow)?
// get exp check into normalize //kinda done
// need to check a sign before add_function (case + - make sub instead)
// fill up an exp and sign in add_function (bits[3])
// figure out result sign
// add NaN INF NINF check in comparison
// rounding
// figure out how to let add overflow while sub
