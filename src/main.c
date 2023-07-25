#include "s21_decimal.h"

void int_to_decimal_test(s21_decimal res, int value);
void float_to_decimal_test(s21_decimal res, float value);
void decimal_to_int_test(s21_decimal res, int value);
void decimal_to_float_test(s21_decimal res, float value);
void is_less_test(s21_decimal value_1, s21_decimal value_2);
void is_greater_test(s21_decimal value_1, s21_decimal value_2);
void is_eq_test(s21_decimal value_1, s21_decimal value_2);
void add_test(s21_decimal value_1, s21_decimal value_2);
void sub_test(s21_decimal value_1, s21_decimal value_2);
void div_test(s21_decimal value_1, s21_decimal value_2);
void mul_test(s21_decimal value_1, s21_decimal value_2);
void add_test_big(s21_decimal_big value_1, s21_decimal_big value_2);
void sub_test_big(s21_decimal_big value_1, s21_decimal_big value_2);
void mul_test_big(s21_decimal_big value_1, s21_decimal_big value_2);
void div_test_big(s21_decimal_big value_1, s21_decimal_big value_2);

int main() {
  s21_decimal value = {{0, 0, 0, 1 << 16}}, res = {0};
  s21_decimal value_1 = {{100, 0, 0, (1 << 16)}};
  s21_decimal value_2 = {{30, 0, 0, (1 << 16)}};
  for (int i = 0; i < 4; i++) {
    printf("%u\t", value.bits[i]);
  }
  printf("\n");
  s21_decimal temp = {0};
  s21_div(value_1, value_2, &temp);
  temp.bits[3] = 22 << 16;
  s21_round(value, &res);
  for (int i = 0; i < 4; i++) {
    printf("%u\t", res.bits[i]);
  }
  printf("%u", res.bits[3] >> 16);

  return 0;
}