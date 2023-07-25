#include "s21_decimal.h"

int s21_add_big(s21_decimal_big value_1, s21_decimal_big value_2,
                s21_decimal_big *result) {
  int value_1_sign = getSignInt(value_1.bits[7]),
      value_2_sign = getSignInt(value_2.bits[7]);
  s21_decimal_big res_big = {0};
  setSignIntBig(0, &value_1);  // !!!
  setSignIntBig(0, &value_2);  // !!!

  if ((value_1_sign ^ value_2_sign) == 0) {
    res_big = add_function_big(value_1, value_2, 0);
  } else if (s21_is_greater_or_equal_big(value_1, value_2)) {
    res_big = sub_function_big(value_1, value_2);
  } else {
    res_big = sub_function_big(value_2, value_1);
  }
  *result = res_big;
  add_sign_chek(value_1_sign, value_2_sign, value_1, value_2, result);
  return 0;
}

int s21_sub_big(s21_decimal_big value_1, s21_decimal_big value_2,
                s21_decimal_big *result) {
  int value_1_sign = getSignInt(value_1.bits[7]),
      value_2_sign = getSignInt(value_2.bits[7]);

  int test = 0;

  setSignIntBig(0, &value_1);  // !!!
  setSignIntBig(0, &value_2);  // !!!

  if (s21_is_less_big(value_1, value_2)) {
    s21_decimal_big temp = value_1;
    value_1 = value_2, value_2 = temp;
    if ((value_1_sign == 1 && value_2_sign == 0) ||
        (value_1_sign == 0 && value_2_sign == 0)) {
      test = 2;
    } else if (value_1_sign == 1 && value_2_sign == 1) {
      test = 3;
    }
  }

  *result = signLogicBig(value_1_sign, value_2_sign, value_1, value_2, test);
  sub_sign_chek(value_1_sign, value_2_sign, test, value_1, value_2, result);
  return 0;
}

int s21_mul_big(s21_decimal_big value_1, s21_decimal_big value_2,
                s21_decimal_big *result) {
  int error = 0;
  int value_1_sign = getSignInt(value_1.bits[7]),
      value_2_sign = getSignInt(value_2.bits[7]);

  int value_1_exp = getExp(value_1.bits[7]),
      value_2_exp = getExp(value_2.bits[7]);

  value_1.bits[7] = 0;
  value_2.bits[7] = 0;

  setSignIntBig(0, &value_1);  // !!!
  setSignIntBig(0, &value_2);  // !!!

  s21_decimal_big res_big = {{0}};
  s21_decimal_big temp_value2 = value_2;
  for (int i = 0; i < 223; i++) {
    if (get_bit_big(value_1, i) == 1) {
      value_2 = setShiftBig(value_2, i);
      s21_add_big(res_big, value_2, &res_big);
    }
    value_2 = temp_value2;
  }

  if ((value_1_exp + value_2_exp) <= 28) {
    res_big.bits[7] = (value_1_exp + value_2_exp) << 16;
  } else {
    if (getSignInt(res_big.bits[7]) == 0) {
      error = 1;
    } else {
      error = 2;
    }
  }

  if ((value_1_sign == 1 || value_2_sign == 1) &&
      (value_1_sign != 1 || value_2_sign != 1))
    setSignIntBig(1, &res_big);

  *result = res_big;
  return error;
}

int s21_div_big(s21_decimal_big value_1, s21_decimal_big value_2,
                s21_decimal_big *result) {
  s21_decimal_big res_big = {{0}};
  s21_decimal_big remainder_val = res_big;
  int error = 0;

  int value_1_sign = getSignInt(value_1.bits[7]),
      value_2_sign = getSignInt(value_2.bits[7]);

  int value_1_exp = getExp(value_1.bits[7]),
      value_2_exp = getExp(value_2.bits[7]);

  int result_exp = value_1_exp - value_2_exp;

  if (result_exp < 0) result_exp *= -1;

  value_1.bits[7] = 0;
  value_2.bits[7] = 0;

  s21_decimal val1 = convertBack(value_1);
  s21_decimal val2 = convertBack(value_2);

  setSignIntBig(0, &value_1);
  setSignIntBig(0, &value_2);
  if (nonZeroNumberBig(value_1) && nonZeroNumberBig(value_2)) {
    if (s21_is_greater(val1, val2)) {
      res_big = divLogicBig(value_1, value_2, &remainder_val);
    } else if (s21_is_equal(val1, val2)) {
      res_big.bits[0] = 1;
    } else {
      s21_decimal_big ten = {{10, 0, 0, 0, 0, 0, 0, 0}};
      if (value_1_exp != 0 || value_2_exp != 0) {
        while (s21_is_greater_big(value_1, value_2) != 1 && error == 0) {
          error = s21_mul_big(value_1, ten, &value_1);
          value_1_exp++;
        }
      }

      if (error == 1) {
        error = 2;
      }
      res_big = divLogicBig(value_1, value_2, &remainder_val);
    }
  } else {
    error = 3;
  }

  if (!nonZeroNumberBig(value_1) && nonZeroNumberBig(value_2)) {
    error = 0;
  }

  result_exp = value_1_exp - value_2_exp;
  if (result_exp < 0) result_exp *= -1;

  if (error == 0 && (value_1_exp != 0 || value_2_exp != 0)) {
    remainder_def(result_exp, remainder_val, value_2, &res_big);
    if (result_exp > 28) {
      error = 2;
    }
  }

  *result = res_big;

  if (value_1_sign == 1 && value_2_sign == 1) {
    result->bits[7] &= PLUS;
  } else if (value_1_sign == 1 && value_2_sign == 0) {
    result->bits[7] |= MINUS;
  } else if (value_1_sign == 0 && value_2_sign == 1) {
    result->bits[7] |= MINUS;
  } else if (value_1_sign == 0 && value_2_sign == 0) {
    result->bits[7] &= PLUS;
  }
  return error;
}
