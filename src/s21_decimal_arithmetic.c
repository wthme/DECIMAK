#include "s21_decimal.h"

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int error = normalize(&value_1, &value_2);
  s21_decimal res = {{0}};
  s21_decimal_big value_1_big = convertBig(value_1);
  s21_decimal_big value_2_big = convertBig(value_2);
  s21_decimal_big res_big = {0};

  if (error != 2) {
    s21_add_big(value_1_big, value_2_big, &res_big);
    if (overflow_check_big(res_big) == 1) {
      if (overflowFix(&res_big) == 1) {
        error = 1;
        if (getSignInt(res_big.bits[7]) == 1) {
          error = 2;
        }
      } else {
        res = convertBack(res_big);
      }
    } else {
      res = convertBack(res_big);
    }
  }

  *result = res;
  return error;
}

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  s21_decimal res = {{0}};
  int error = normalize(&value_1, &value_2);
  s21_decimal_big value_1_big = convertBig(value_1);
  s21_decimal_big value_2_big = convertBig(value_2);
  s21_decimal_big res_big = {{0}};

  if (error != 2) {
    s21_sub_big(value_1_big, value_2_big, &res_big);
    if (overflow_check_big(res_big) == 1) {
      if (overflowFix(&res_big) == 1) {
        error = 1;
        if (getSignInt(res_big.bits[7]) == 1) {
          error = 2;
        }
      } else {
        res = convertBack(res_big);
      }
    } else {
      res = convertBack(res_big);
    }
  }

  *result = res;
  return error;
}

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  s21_decimal res = {{0}};
  s21_decimal_big value_1_big = convertBig(value_1);
  s21_decimal_big value_2_big = convertBig(value_2);
  s21_decimal_big res_big = {{0}};
  int error = s21_mul_big(value_1_big, value_2_big, &res_big);

  if (error == 0) {
    if (overflow_check_big(res_big) == 1) {
      if (overflowFix(&res_big) == 1) {
        error = 1;
        if (getSignInt(res_big.bits[7]) == 1) {
          error = 2;
        }
      } else {
        res = convertBack(res_big);
      }
    } else {
      res = convertBack(res_big);
    }
  }
  *result = res;
  return error;
}

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  s21_decimal res = {{0}};
  s21_decimal_big value_1_big = convertBig(value_1);
  s21_decimal_big value_2_big = convertBig(value_2);
  s21_decimal_big res_big = {{0}};
  int error = s21_div_big(value_1_big, value_2_big, &res_big);
  if (error == 0) {
    if (overflow_check_big(res_big) == 1) {
      if (overflowFix(&res_big) == 1) {
        error = 1;
        if (getSignInt(res_big.bits[7]) == 1) {
          error = 2;
        }
      } else {
        res = convertBack(res_big);
      }
    } else {
      res = convertBack(res_big);
    }
  }

  *result = res;
  return error;
}
