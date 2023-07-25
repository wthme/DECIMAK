#include "s21_decimal.h"

int s21_floor(s21_decimal value, s21_decimal *result) {
  int error_temp = 0, error = 0, res_sign = getSignInt(value.bits[3]),
      exp = getExp(value.bits[3]);
  setSignInt(0, &value);
  for (int i = 0; i < 4; i++) result->bits[i] = 0;
  s21_decimal_big result_big = {0}, value_big, remainder_val = {0},
                  one = {{1, 0, 0, 0, 0, 0, 0, 0}},
                  ten = {{10, 0, 0, 0, 0, 0, 0, 1 << 16}},
                  del = {{10, 0, 0, 0, 0, 0, 0, 1 << 16}}, temp = {{0}};
  for (int i = 0; i < exp - 1; i++) {
    error_temp = (s21_mul_big(del, ten, &del));
    if (error_temp != 0) error = 1;
  }
  value_big = convertBig(value);
  if (exp > 28)
    error = 1;
  else if (exp != 0) {
    error_temp = s21_div_big_ten(value_big, del, &temp, &remainder_val);
    if (error_temp != 0) error = 1;
    if (res_sign == 1) {
      error_temp = (s21_add_big(temp, one, &result_big));
      if (error_temp != 0) error = 1;
    } else {
      result_big = temp;
    }
    *result = convertBack(result_big);
  } else {
    *result = value;
  }
  if (res_sign == 1) {
    setSignInt(1, result);
  }
  if (error != 0) error = 1;
  return error;
}

int s21_round(s21_decimal value, s21_decimal *result) {
  int error = 0, res_sign = value.bits[3] >> 31,
      exp = (((value.bits[3] << 1) >> 1) >> 16);
  value.bits[3] = ((value.bits[3] << 1) >> 1);
  s21_decimal_big temp_value = convertBig(value),
                  one = {{1, 0, 0, 0, 0, 0, 0, 0}},
                  five = {{5, 0, 0, 0, 0, 0, 0, 1 << 16}},
                  ten = {{10, 0, 0, 0, 0, 0, 0, 1 << 16}}, res = {{0}},
                  remainder = {{0}},
                  ten_div = {{10, 0, 0, 0, 0, 0, 0, 1 << 16}};
  for (int i = 0; i < 4; i++) result->bits[i] = 0;
  if (exp > 28)
    error = 1;
  else if (exp == 0)
    *result = value;
  else {
    for (int i = 0; i < (exp - 1); i++) {
      if (s21_mul_big(ten, ten_div, &ten_div) != 0) error = 1;
    }
    if (error == 0) {
      if (s21_div_big_ten(temp_value, ten_div, &res, &remainder) != 0)
        error = 1;
      else {
        res.bits[7] = 0;
        remainder.bits[7] = exp << 16;
        if (s21_is_greater_or_equal_big(remainder, five) == 1) {
          error = s21_add_big(res, one, &res);
        }
        *result = convertBack(res);
        if (res_sign == 1) result->bits[3] = result->bits[3] + (1 << 31);
      }
    }
  }
  if (error != 0) error = 1;
  return error;
}

int s21_truncate(s21_decimal value, s21_decimal *result) {
  int error = 0, res_sign = value.bits[3] >> 31,
      exp = (((value.bits[3] << 1) >> 1) >> 16);
  value.bits[3] = ((value.bits[3] << 1) >> 1);
  s21_decimal_big temp_value = convertBig(value),
                  ten = {{10, 0, 0, 0, 0, 0, 0, 1 << 16}},
                  ten_div = {{10, 0, 0, 0, 0, 0, 0, 1 << 16}}, res = {{0}},
                  remainder = {{0}};
  for (int i = 0; i < 4; i++) result->bits[i] = 0;
  if (exp > 28)
    error = 1;
  else if (exp == 0)
    *result = value;
  else {
    for (int i = 0; i < (exp - 1); i++) {
      if (s21_mul_big(ten, ten_div, &ten_div) != 0) error = 1;
    }
    if (error == 0) {
      error = s21_div_big_ten(temp_value, ten_div, &res, &remainder);
      res.bits[7] = 0;
      *result = convertBack(res);
      if (res_sign == 1) result->bits[3] = result->bits[3] + (1 << 31);
    }
  }
  if (error != 0) error = 1;
  return error;
}

int s21_negate(s21_decimal value, s21_decimal *result) {
  int error = 0, exp = (((value.bits[3] << 1) >> 1) >> 16);
  s21_decimal temp = {{1, 0, 0, 1 << 31}};
  for (int i = 0; i < 4; i++) result->bits[i] = 0;
  if (exp > 28)
    error = 1;
  else if (s21_mul(value, temp, result) != 0)
    error = 1;
  return error;
}

/*int s21_round(s21_decimal value, s21_decimal *result) {
  int error = 0, res_sign = getSignInt(value.bits[3]);//,
     // exp = getExp(value.bits[3]);
  for (int i = 0; i < 4; i++) result->bits[i] = 0;
  value.bits[3] = ((value.bits[3] << 1) >> 1);
  s21_decimal int_part = {{0}}, remainder = {{0}}, one = {{1, 0, 0, 0}},
              five = {{5, 0, 0, 1 << 16}};
  remainder = s21_div_part(value, one, &int_part);
  if (s21_is_greater_or_equal(remainder, five) == 1) {
    s21_add(int_part, one, result);
  } else {
    *result = int_part;
  }
  if (res_sign == 1) result->bits[3] = 1 << 31;
  return error;
}*/

/*int s21_round(s21_decimal value, s21_decimal *result) {
  int error = 0, res_sign = getSignInt(value.bits[3]), last_digit = 0,
      exp = getExp(value.bits[3]);
  setSignInt(0, &value);
  s21_decimal one = {{1, 0, 0, 0}}, five = {{5, 0, 0, 0}},
              ten = {{10, 0, 0, 0}}, temp = {{0}}, remainder_val = {{0}},
              first_num = {{0}}, aboba = {{0}}, zero = {{0}};
  remainder_val = s21_div_part(value, one, &temp);  // дробная часть числа
  remainder_val.bits[3] = 0;
  last_digit = get_bit(temp, 0);  // последняя цифра целой части числа
  if (exp > 1) {
    for (int i = 0; i < exp - 1; i++) {
      first_num = s21_div_part(remainder_val, ten,
                               &aboba);  // первая цифра дробной части числа
      remainder_val = aboba;
    }
  } else {
    first_num = remainder_val;
  }
  if (exp != 0 && !s21_is_equal(temp, zero)) {
    if (s21_is_equal(first_num, five)) {
      if (last_digit == 1) {
        s21_add(temp, one, result);
      } else {
        s21_sub(temp, one, result);
      }
    } else if (s21_is_greater(first_num, five)) {
      s21_add(temp, one, result);
    } else {
      s21_sub(temp, one, result);
    }

  } else {
    *result = value;
  }
  if (res_sign == 1) {
    setBit(127, result);
  }
  return error;
}*/

/*int s21_truncate(s21_decimal value, s21_decimal *result) {
  int error = 0, res_sign = getSignInt(value.bits[3]),
      exp = getExp(value.bits[3]);
  for (int i = 0; i < 4; i++) result->bits[i] = 0;
  setSignInt(0, &value);
  s21_decimal temp = {{1, 0, 0, 0}};
  if (exp != 0) {
    s21_div_part(value, temp, result);  // ? мб юзать divLogic, а не s21_div?
  } else {
    *result = value;
  }
  if (res_sign == 1) {
    setBit(127, result);
  }
  return error;
}*/

/*int s21_negate(s21_decimal value, s21_decimal *result) {
  int error = 0, sign = getSignInt(value.bits[3]);
  for (int i = 0; i < 4; i++) result->bits[i] = 0;
  *result = value;
  if (sign == 1) {
    setSignInt(0, result);
  } else {
    setSignInt(1, result);
  }
  return error;
}*/
