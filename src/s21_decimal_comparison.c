#include "s21_decimal.h"

int s21_is_less(s21_decimal value_1, s21_decimal value_2) {
  int sign_1 = getSignInt(value_1.bits[3]),
      sign_2 = getSignInt(value_2.bits[3]),
      error = normalize(&value_1, &value_2), res = 0;
  if (error != 2) {
    if ((sign_1 == 1) && (sign_2 == 0))
      res = 1;
    else if ((sign_1 == 0) && (sign_2 == 1))
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
    if ((sign_1 == 1) && (sign_2 == 1)) res = !res;
  }
  return res;
}

int s21_is_less_or_equal(s21_decimal value_1, s21_decimal value_2) {
  return (s21_is_less(value_1, value_2) || (s21_is_equal(value_1, value_2)));
}

int s21_is_greater(s21_decimal value_1, s21_decimal value_2) {
  int sign_1 = getSignInt(value_1.bits[3]),
      sign_2 = getSignInt(value_2.bits[3]),
      error = normalize(&value_1, &value_2), res = 0;
  if (error != 2) {
    if ((sign_1 == 0) && (sign_2 == 1))
      res = 1;
    else if ((sign_1 == 1) && (sign_2 == 0))
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
    if ((sign_1 == 1) && (sign_2 == 1)) res = !res;
  }
  return res;
}

int s21_is_greater_or_equal(s21_decimal value_1, s21_decimal value_2) {
  return (s21_is_greater(value_1, value_2) || (s21_is_equal(value_1, value_2)));
}

int s21_is_equal(s21_decimal value_1, s21_decimal value_2) {
  int res = 1, sign_1 = getSignInt(value_1.bits[3]),
      sign_2 = getSignInt(value_2.bits[3]),
      error = normalize(&value_1, &value_2);
  if (error != 2) {
    if ((isZero(value_1) == 1) && (isZero(value_2) == 1))
      res = 1;
    else if ((sign_1 ^ sign_2) == 0) {
      if (getExp(value_1.bits[3]) == getExp(value_2.bits[3])) {
        for (int i = 95; i >= 0; i--) {
          if (get_bit(value_1, i) != get_bit(value_2, i)) {
            res = 0;
            break;
          }
        }
      }  // else
         // res = 0;
    } else
      res = 0;
  }
  return res;
}

int s21_is_not_equal(s21_decimal value_1, s21_decimal value_2) {
  return (!(s21_is_equal(value_1, value_2)));
}
