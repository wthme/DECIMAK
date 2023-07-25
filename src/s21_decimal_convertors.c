#include "s21_decimal.h"

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  int error = 0;
  for (int i = 0; i < 4; i++) dst->bits[i] = 0;
  if (src == 0)
    dst->bits[0] = 0;
  else if ((src >= MAX_DECIMAL) || (src <= MIN_DECIMAL)) {
    error = 1;
  } else {
    if (src < 0) {
      src = -src;
      dst->bits[3] = MINUS;
    }
    int mask = 0xFFFFFFFF;
    dst->bits[0] = src & mask;
  }
  return error;
}

/*int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  int error = 0, sign = 0;
  if (src < 0) {
    sign = 1;
    src = -src;
  }
  for (int i = 0; i < 4; i++)
    dst->bits[i] = 0;
  for (int i = 95; i >= 0; i--) {
    if ((src - pow(2, i)) >= 0) {
      setBit(i, dst);
      src = src - pow(2, i);
    }
  }
  if (sign == 1) {
    dst->bits[3] = 1 << 31;
  }
  if (src != 0) {
    error = 1;
  }
  return error;
}*/

/*int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  unsigned int *p = (void *)&src;
  unsigned int bits = *p;
  int exp = ((bits << 1) >> 24) - 127;
  unsigned int mant = (bits << 9) >> 9;
  unsigned int mask = 0xFFFFFFFE;
  int count = 0;
  mant = mant | (1 << 23);
  while (1) {
    if (mant & mask == 0)
      mant = mant >> 1;
    else
      break;
  }
  unsigned int temp_mant = mant;
  for (int i = 0; i < 32; i++) {
    if (temp_mant & 1 == 1)
      count = i;
    temp_mant = temp_mant >> 1;
  }
  exp = exp - count;
  s21_decimal dec1 = {mant, 0, 0, 0};
  s21_decimal dec2 = {1, 0, 0, 0};
  s21_decimal mul = {2, 0, 0, 0};
  for (int i = 0; i < abs(exp); i++)
    s21_mul(dec2, mul, &dec2);
  if (exp < 0)
    s21_div(dec1, dec2, dst);
  else
    s21_mul(dec1, dec2, dst);
}*/

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  int error = 0, scale = 8, minus = 0;
  for (int i = 0; i < 4; i++) dst->bits[i] = 0;
  if ((fabs(src) < powl(10.0, -1 * 28)) & (fabs(src) > 0.0))
    error = 1;
  else if ((src >= MAX_DECIMAL) || (src <= MIN_DECIMAL))
    error = 1;
  else if ((src != src) || (isinf(src) == 1)) {
    error = 1;
  } else {
    if (src < 0) {
      src = -src;
      minus = 1;
    }
    unsigned int temp = (int)src;
    double tempDouble = src - temp;
    unsigned int tempInt = tempDouble * pow(10, 8);
    /*if (tempInt == 0)
      scale = 1;
    else {
      while (1) {
        if (tempInt % 10 == 0) {
          tempInt = tempInt / 10;
          scale--;
        } else
          break;
        if (scale == 1) break;
      }
    }*/
    s21_decimal value_1 = {{temp, 0, 0, 0}};
    s21_decimal value_2 = {{tempInt, 0, 0, scale << 16}};
    s21_add(value_1, value_2, dst);
    if (minus == 1) dst->bits[3] |= MINUS;
  }
  return error;
}

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  int error = 0, exp = getExp(src.bits[3]), sign = src.bits[3] >> 31;
  if (exp != 0) {
    s21_decimal temp = {{0}};
    s21_truncate(src, &temp);
    if (((temp.bits[1] != 0) || (temp.bits[2] != 0)) ||
        ((sign == 0) & (temp.bits[0] > 2147483647)) ||
        ((sign == 1) & (temp.bits[0] > 2147483648)))
      error = 1;
    else {
      *dst = temp.bits[0];
      if (sign == 1) *dst = -*dst;
    }
  } else if (((src.bits[1] != 0) || (src.bits[2] != 0)) ||
             ((sign == 0) & (src.bits[0] > 2147483647)) ||
             ((sign == 1) & (src.bits[0] > 2147483648)))
    error = 1;
  else {
    *dst = src.bits[0];
    if (sign == 1) *dst = -*dst;
  }
  return error;
}

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  int error = 0, exp = getExp(src.bits[3]), sign = src.bits[3] >> 31;
  s21_decimal check = {{1, 0, 0, 28 << 16}}, zero = {{0, 0, 0, 0}};
  src.bits[3] = ((src.bits[3] << 1) >> 1);
  *dst = 0.0;
  if ((exp > 28) ||
      ((s21_is_less(src, check) == 1) & (s21_is_greater(src, zero)))) {
    error = 1;
    for (int i = 0; i < 4; i++) src.bits[i] = 0;
  } else {
    if (exp > 6) {
      src.bits[3] = ((exp - 6) << 16);
      s21_round(src, &src);
      for (int i = 0; i < 4; i++) printf("%u\t", src.bits[i]);
      printf("\n");
      src.bits[3] = 6 << 16;
      exp = 6;
    }
    s21_decimal temp = {0};
    s21_truncate(src, &temp);
    *dst = temp.bits[0];
    s21_decimal sub = {0};
    s21_sub(src, temp, &sub);
    // float flt_rem = sub.bits[0] / pow(10, exp);
    //*dst = *dst + flt_rem;
    *dst += sub.bits[0] / pow(10, exp);
  }
  if (sign == 1) *dst = -*dst;
  return error;
}
