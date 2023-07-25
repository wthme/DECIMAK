#include "s21_test_decimal.h"

START_TEST(test_div_positive_int) {
  srand(time(NULL));
  long long a = random_ll();
  long long b = random_ll();
  long long expected = a / b;

  s21_decimal res = {0};
  s21_decimal expected_decimal = convert_ll_to_decimal(expected);
  s21_decimal a_decimal = convert_ll_to_decimal(a);
  s21_decimal b_decimal = convert_ll_to_decimal(b);
  int code = s21_div(a_decimal, b_decimal, &res);
  code = code;
  ck_assert_int_eq(s21_is_equal(res, expected_decimal), true);
}
END_TEST

START_TEST(test_div_negative_int) {
  srand(time(NULL));
  long long a = random_ll();
  long long b = random_ll();
  long long expected = (a * -1) / b;
  s21_decimal res = {0};
  s21_decimal expected_decimal = convert_ll_to_decimal(expected);
  s21_decimal a_decimal = convert_ll_to_decimal(a);
  s21_decimal b_decimal = convert_ll_to_decimal(b);
  setSignInt(1, &a_decimal);

int code = s21_div(a_decimal, b_decimal, &res);
code = code;
  ck_assert_int_eq(s21_is_equal(res, expected_decimal), true);

  setSignInt(1, &b_decimal);
  expected = (a * -1) / (b * -1);
  expected_decimal = convert_ll_to_decimal(expected);
code = s21_div(a_decimal, b_decimal, &res);
  ck_assert_int_eq(s21_is_equal(res, expected_decimal), true);
  setSignInt(0, &a_decimal);
  setSignInt(1, &b_decimal);
  expected = (a) / (b * -1);
  expected_decimal = convert_ll_to_decimal(expected);
code = s21_div(a_decimal, b_decimal, &res);
  ck_assert_int_eq(s21_is_equal(res, expected_decimal), true);
}
END_TEST

START_TEST(test_div_positive_float) {
  srand(time(NULL));
  float a = 8920.772461;
  float b = 1864.033691;
  float expected = a / b;
  s21_decimal res = {0};
  s21_decimal expected_decimal = {0};
  s21_decimal a_decimal = {0};
  s21_decimal b_decimal = {0};
  s21_from_float_to_decimal(expected, &expected_decimal);
  s21_from_float_to_decimal(b, &b_decimal);
  s21_from_float_to_decimal(a, &a_decimal);

  int code = s21_div(a_decimal, b_decimal, &res);

  float got_float = 0;
  s21_from_decimal_to_float(res, &got_float);

  ck_assert_int_eq(code, 0);
  ck_assert_float_eq_tol(got_float, expected, 1e-06);
}
END_TEST

START_TEST(test_div_negative_float) {
  srand(time(NULL));
  float a = random_float(0.00000, 9000.99999);
  float b = random_float(0.00000, 9000.99999);
  float expected = (a * (-1)) / b;

  s21_decimal res = {0};
  s21_decimal expected_decimal = {0};
  s21_decimal a_decimal = {0};
  s21_decimal b_decimal = {0};
  s21_from_float_to_decimal(expected, &expected_decimal);
  s21_from_float_to_decimal(b, &b_decimal);
  s21_from_float_to_decimal(a, &a_decimal);
  setSignInt(1, &a_decimal);

  int code = s21_div(a_decimal, b_decimal, &res);

  float got_float = 0;
  s21_from_decimal_to_float(res, &got_float);

  ck_assert_int_eq(code, 0);
  ck_assert_float_eq_tol(got_float, expected, 1e-06);

  expected = (a * (-1)) / (b * (-1));
  s21_from_float_to_decimal(expected, &expected_decimal);
  setSignInt(1, &b_decimal);
  code = s21_div(a_decimal, b_decimal, &res);
  got_float = 0;
  s21_from_decimal_to_float(res, &got_float);

  ck_assert_int_eq(code, 0);
  ck_assert_float_eq_tol(got_float, expected, 1e-06);

  expected = a / (b * (-1));
  s21_from_float_to_decimal(expected, &expected_decimal);
  setSignInt(1, &b_decimal);
  setSignInt(0, &a_decimal);
  code = s21_div(a_decimal, b_decimal, &res);
  got_float = 0;
  s21_from_decimal_to_float(res, &got_float);
  ck_assert_int_eq(code, 0);
  ck_assert_float_eq_tol(got_float, expected, 1e-06);
}
END_TEST

START_TEST(test_div_super_big_number) {
  s21_decimal res = {0};
  s21_decimal expected_decimal = {{1717986, 0, 0, 0}};
  s21_decimal a_decimal = {{214748363, 214748363, 214748363, 0}};
  s21_decimal b_decimal = {{125, 125, 125, 0}};
  int code = s21_div(a_decimal, b_decimal, &res);
  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(s21_is_equal(res, expected_decimal), true);

  s21_decimal expected_decimal2 = {{1717986, 0, 0, 0}};
  s21_decimal a_decimal2 = {{214748363, 214748363, 214748363, 0}};
  s21_decimal b_decimal2 = {{125, 125, 125, 0}};
  setSignInt(1, &a_decimal2);
  setSignInt(1, &expected_decimal2);
  code = s21_div(a_decimal2, b_decimal2, &res);
  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(s21_is_equal(res, expected_decimal2), true);

s21_decimal expected_decimal3 = {{0, 0, 0, 0}};
  s21_decimal a_decimal3 = {{5, 0, 0, 0}};
  s21_decimal b_decimal3 = {{4294967295, 4294967295, 4294967295, 0}};
  code = s21_div(a_decimal3, b_decimal3, &res);
  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(s21_is_equal(res, expected_decimal3), true);

  s21_decimal expected_decimal4 = {{0, 0, 0, 0}};
  s21_decimal a_decimal4 = {{5, 0, 0, (1 << 16)}};
  s21_decimal b_decimal4 = {{4294967295, 4294967295, 4294967295, 0}};
  code = s21_div(a_decimal4, b_decimal4, &res);
  ck_assert_int_eq(code, 2);
  ck_assert_int_eq(s21_is_equal(res, expected_decimal4), true);

  s21_decimal expected_decimal6 = {{1, 0, 0, (22 << 16)}};
  s21_decimal a_decimal6 = {{429496729, 4294967295, 4294967295, (22 << 16)}};
  s21_decimal b_decimal6 = {{429496729, 4294967295, 4294967295, 0}};
  setSignInt(1, &a_decimal6);
  setSignInt(1, &expected_decimal6);
  code = s21_div(a_decimal6, b_decimal6, &res);
  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(s21_is_equal(res, expected_decimal6), true);
}
END_TEST

START_TEST(test_div_zero) {
  s21_decimal res = {0};
  s21_decimal expected_decimal4 = {{0, 0, 0, 0}};
  s21_decimal a_decimal4 = {{2, 2, 2, (1 << 16)}};
  s21_decimal b_decimal4 = {{0, 0, 0, 0}};
  int code = s21_div(a_decimal4, b_decimal4, &res);
  ck_assert_int_eq(code, 3);
  ck_assert_int_eq(s21_is_equal(res, expected_decimal4), true);

  s21_decimal expected_decimal5 = {{0, 0, 0, 0}};
  s21_decimal a_decimal5 = {{0, 0, 0, (1 << 16)}};
  s21_decimal b_decimal5 = {{0, 0, 2, 0}};
  code = s21_div(a_decimal5, b_decimal5, &res);
  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(s21_is_equal(res, expected_decimal5), true);
}
END_TEST

START_TEST(test_div_max) {
  s21_decimal res = {0};
  s21_decimal expected_decimal4 = {{0, 0, 0, 0}};
  s21_decimal a_decimal = {{1, 0, 0, (1 << 16)}};
  s21_decimal b_decimal = {{4294967295, 4294967295, 4294967295, 0}};
  int code = s21_div(a_decimal, b_decimal, &res);
  ck_assert_int_eq(code, 2);
  ck_assert_int_eq(s21_is_equal(res, expected_decimal4), true);

  s21_decimal expected_decimal2 = {{0, 0, 0, 0}};
  s21_decimal a_decimal2 = {{1, 1, 1, (120 << 16)}};
  s21_decimal b_decimal2 = {{1, 1, 1, (28 << 16)}};
  code = s21_div(a_decimal2, b_decimal2, &res);
  ck_assert_int_eq(code, 2);
  ck_assert_int_eq(s21_is_equal(res, expected_decimal2), true);
}
END_TEST

Suite *s21_test_div() {
  Suite *s = NULL;
  TCase *tc_core = NULL;

  s = suite_create("s21_div");
  tc_core = tcase_create("Core");
  tcase_add_test(tc_core, test_div_positive_int);
  tcase_add_test(tc_core, test_div_negative_int);
  tcase_add_test(tc_core, test_div_positive_float);
  tcase_add_test(tc_core, test_div_negative_float);
  // tcase_add_test(tc_core, test_div_big_decimal);
  tcase_add_test(tc_core, test_div_super_big_number);
  tcase_add_test(tc_core, test_div_zero);
  tcase_add_test(tc_core, test_div_max);
  suite_add_tcase(s, tc_core);
  return s;
}