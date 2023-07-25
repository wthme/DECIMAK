#include "s21_test_decimal.h"

START_TEST(test_convertors_positive_int) {
  int value = 15;
  s21_decimal decimal = {{0}};
  int res = 0;
  ck_assert(s21_from_int_to_decimal(value, &decimal) == 0);
  ck_assert(s21_from_decimal_to_int(decimal, &res) == 0);
  ck_assert_int_eq(value, res);
}
END_TEST

START_TEST(test_convertors_negatives_int) {
  int value = -15;
  s21_decimal decimal = {{0}};
  int res = 0;
  ck_assert(s21_from_int_to_decimal(value, &decimal) == 0);
  ck_assert(s21_from_decimal_to_int(decimal, &res) == 0);
  ck_assert_int_eq(value, res);
}
END_TEST

START_TEST(test_convertors_positive_float) {
  float value = 15.25;
  s21_decimal decimal = {{0}};
  float res = 0;
  ck_assert(s21_from_float_to_decimal(value, &decimal) == 0);
  ck_assert(s21_from_decimal_to_float(decimal, &res) == 0);
  ck_assert_ldouble_eq_tol(value, res, 1e-6);
}
END_TEST

START_TEST(test_convertors_negatives_float) {
  float value = -15.25;
  s21_decimal decimal = {{0}};
  float res = 0;
  ck_assert(s21_from_float_to_decimal(value, &decimal) == 0);
  ck_assert(s21_from_decimal_to_float(decimal, &res) == 0);
  ck_assert_ldouble_eq_tol(value, res, 1e-6);
}
END_TEST

START_TEST(test_convertors_positives_float_to_int) {
  float value = 15.25;
  s21_decimal decimal = {{0}};
  int res = value;
  int dec_res = 0;
  ck_assert(s21_from_float_to_decimal(value, &decimal) == 0);
  ck_assert(s21_from_decimal_to_int(decimal, &dec_res) == 0);
  ck_assert_int_eq(res, dec_res);
}
END_TEST

START_TEST(test_convertors_negatives_float_to_int) {
  float value = -15.25;
  s21_decimal decimal = {{0}};
  int res = value;
  int dec_res = 0;
  ck_assert(s21_from_float_to_decimal(value, &decimal) == 0);
  ck_assert(s21_from_decimal_to_int(decimal, &dec_res) == 0);
  ck_assert_int_eq(res, dec_res);
}

START_TEST(test_convertors_zero_int) {
  int value = 0, res = 0;
  s21_decimal decimal = {{0}};
  ck_assert(s21_from_int_to_decimal(value, &decimal) == 0);
  ck_assert(s21_from_decimal_to_int(decimal, &res) == 0);
  ck_assert_int_eq(res, value);
}
END_TEST

START_TEST(test_convertors_zero_float) {
  float value = 0.0, res = 0.0;
  s21_decimal decimal = {{0}};
  ck_assert(s21_from_float_to_decimal(value, &decimal) == 0);
  ck_assert(s21_from_decimal_to_float(decimal, &res) == 0);
  ck_assert_ldouble_eq(res, value);
}
END_TEST

START_TEST(test_convertors_nan) {
  float value = S21_NAN;
  s21_decimal decimal = {{0}};
  ck_assert(s21_from_float_to_decimal(value, &decimal) == 1);
}
END_TEST

START_TEST(test_convertors_max) {
  float value = MAX_DECIMAL;
  s21_decimal decimal = {{0}};
  ck_assert(s21_from_float_to_decimal(value, &decimal) == 1);
}
END_TEST

START_TEST(test_convertors_min) {
  float value = MIN_DECIMAL;
  s21_decimal decimal = {{0}};
  ck_assert(s21_from_float_to_decimal(value, &decimal) == 1);
}
END_TEST

START_TEST(test_convertors_zero_scale) {
  float value = 10.0, res = 0.0;
  s21_decimal decimal = {{0}};
  ck_assert(s21_from_float_to_decimal(value, &decimal) == 0);
  ck_assert(s21_from_decimal_to_float(decimal, &res) == 0);
  ck_assert_ldouble_eq(value, res);
}
END_TEST

START_TEST(test_convertors_int_max) {
  int value = 0;
  s21_decimal decimal = {{123, 1, 0, 0}};
  ck_assert(s21_from_decimal_to_int(decimal, &value) == 1);
}
END_TEST

START_TEST(test_convertors_int_max_2) {
  int value = 0;
  s21_decimal decimal = {{123, 0, 1, 0}};
  ck_assert(s21_from_decimal_to_int(decimal, &value) == 1);
}
END_TEST

START_TEST(test_convertors_int_max_3) {
  int value = 0;
  s21_decimal decimal = {{123, 1, 1, 0}};
  ck_assert(s21_from_decimal_to_int(decimal, &value) == 1);
}
END_TEST

START_TEST(test_convertors_int_max_4) {
  int value = 0;
  s21_decimal decimal = {{2147483655, 0, 0, 0}};
  ck_assert(s21_from_decimal_to_int(decimal, &value) == 1);
}
END_TEST

START_TEST(test_convertors_int_max_5) {
  int value = 0;
  s21_decimal decimal = {{2147483655, 0, 0, 1 << 31}};
  ck_assert(s21_from_decimal_to_int(decimal, &value) == 1);
}
END_TEST

START_TEST(test_convertors_int_max_6) {
  int value = 0;
  s21_decimal decimal = {{2147483655, 0, 0, 4 << 16}};
  ck_assert(s21_from_decimal_to_int(decimal, &value) == 0);
}
END_TEST

START_TEST(test_convertors_int_max_7) {
  int value = 0;
  s21_decimal decimal = {{2147483655, 0, 0, (1 << 31) + (4 << 16)}};
  ck_assert(s21_from_decimal_to_int(decimal, &value) == 0);
}
END_TEST

START_TEST(test_convertors_zero) {
  float value = 0.0, res = 0.0;
  s21_decimal decimal = {{0}};
  ck_assert(s21_from_float_to_decimal(value, &decimal) == 0);
  ck_assert(s21_from_decimal_to_float(decimal, &res) == 0);
  ck_assert_ldouble_eq(res, value);
}
END_TEST

START_TEST(test_convertors_max_8) {
  s21_decimal decimal = {{4294967295, 100, 0, 1 << 16}};
  int res = 0;
  ck_assert(s21_from_decimal_to_int(decimal, &res) == 1);
}

/*START_TEST(test_convertors_random) {
  srand(time(NULL));
  float a = random_float(0.00, 9000.99999);
  s21_decimal decimal = {{0}};
  s21_from_float_to_decimal(a, &decimal);
  float res = 0.0;
  s21_from_decimal_to_float(decimal, &res);
  ck_assert_float_eq_tol(a, res, 1e-06);
}
END_TEST

START_TEST(test_convertors_random_negative) {
  srand(time(NULL));
  float a = random_float(0.00, 9000.99999) * -1;
  s21_decimal decimal = {{0}};
  s21_from_float_to_decimal(a, &decimal);
  float res = 0.0;
  s21_from_decimal_to_float(decimal, &res);
  ck_assert_float_eq_tol(a, res, 1e-06);
}
END_TEST*/

Suite *s21_test_convertors() {
  Suite *s = NULL;
  TCase *tc_core = NULL;

  s = suite_create("s21_convertors");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_convertors_positive_int);
  tcase_add_test(tc_core, test_convertors_negatives_int);
  tcase_add_test(tc_core, test_convertors_positive_float);
  tcase_add_test(tc_core, test_convertors_negatives_float);
  tcase_add_test(tc_core, test_convertors_positives_float_to_int);
  tcase_add_test(tc_core, test_convertors_negatives_float_to_int);
  tcase_add_test(tc_core, test_convertors_zero_int);
  tcase_add_test(tc_core, test_convertors_zero_float);
  tcase_add_test(tc_core, test_convertors_nan);
  tcase_add_test(tc_core, test_convertors_max);
  tcase_add_test(tc_core, test_convertors_min);
  tcase_add_test(tc_core, test_convertors_zero_scale);
  tcase_add_test(tc_core, test_convertors_int_max);
  tcase_add_test(tc_core, test_convertors_int_max_2);
  tcase_add_test(tc_core, test_convertors_int_max_3);
  tcase_add_test(tc_core, test_convertors_int_max_4);
  tcase_add_test(tc_core, test_convertors_int_max_5);
  tcase_add_test(tc_core, test_convertors_int_max_6);
  tcase_add_test(tc_core, test_convertors_int_max_7);
  tcase_add_test(tc_core, test_convertors_zero);
  tcase_add_test(tc_core, test_convertors_max_8);
  /*tcase_add_test(tc_core, test_convertors_random);
  tcase_add_test(tc_core, test_convertors_random_negative);*/
  suite_add_tcase(s, tc_core);
  return s;
}
