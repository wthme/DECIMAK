#include "s21_test_decimal.h"

START_TEST(test_mul_positive_int) {  // 200 - 500 = -300
  srand(time(NULL));
  long long a = random_ll() / 2;
  long long b = random_ll() / 2;
  long long expected = a * b;
  s21_decimal res = {0};
  s21_decimal expected_decimal = convert_ll_to_decimal(expected);
  s21_decimal a_decimal = convert_ll_to_decimal(a);
  s21_decimal b_decimal = convert_ll_to_decimal(b);
  int code = s21_mul(a_decimal, b_decimal, &res);
  code = code;
  ck_assert_int_eq(s21_is_equal(res, expected_decimal), true);
}
END_TEST

START_TEST(test_mul_negative_int) {  // 200 - 500 = -300
  srand(time(NULL));
  long long a = random_ll() / 2;
  long long b = random_ll() / 2;
  long long expected = (a * (-1)) * b;
  s21_decimal res = {0};
  s21_decimal expected_decimal = convert_ll_to_decimal(expected);
  s21_decimal a_decimal = convert_ll_to_decimal(a);
  setSignInt(1, &a_decimal);
  s21_decimal b_decimal = convert_ll_to_decimal(b);
  int code = s21_mul(a_decimal, b_decimal, &res);
  code = code;
  ck_assert_int_eq(s21_is_equal(res, expected_decimal), true);

  expected = a * (b * (-1));
  expected_decimal = convert_ll_to_decimal(expected);
  setSignInt(0, &a_decimal);
  setSignInt(1, &b_decimal);
  code = s21_mul(a_decimal, b_decimal, &res);
  ck_assert_int_eq(s21_is_equal(res, expected_decimal), true);

  expected = (a * (-1)) * (b * (-1));
  expected_decimal = convert_ll_to_decimal(expected);
  setSignInt(1, &a_decimal);
  setSignInt(1, &b_decimal);
  code = s21_mul(a_decimal, b_decimal, &res);
  ck_assert_int_eq(s21_is_equal(res, expected_decimal), true);
}
END_TEST

START_TEST(test_mul_positive_float) {  // 200 - 500 = -300
  srand(time(NULL));
  float a = random_float(0.00, 1000.99999);
  float b = random_float(0.00, 1000.99999);
  float expected = a * b;

  s21_decimal res = {0};
  s21_decimal expected_decimal = {0};
  s21_decimal a_decimal = {0};
  s21_decimal b_decimal = {0};
  s21_from_float_to_decimal(expected, &expected_decimal);
  s21_from_float_to_decimal(a, &a_decimal);
  s21_from_float_to_decimal(b, &b_decimal);

  int code = s21_mul(a_decimal, b_decimal, &res);
  float got_float = 0;
  s21_from_decimal_to_float(res, &got_float);
  ck_assert_int_eq(code, 0);
  ck_assert_float_eq_tol(got_float, expected, 1e-06);
}
END_TEST

START_TEST(test_mul_negative_float) {  // 200 - 500 = -300
  srand(time(NULL));
  float a = random_float(0.00, 1000.99999);
  float b = random_float(0.00, 1000.99999);
  float expected = (a * (-1)) * b;

  s21_decimal res = {0};
  s21_decimal expected_decimal = {0};
  s21_decimal a_decimal = {0};
  s21_decimal b_decimal = {0};
  s21_from_float_to_decimal(expected, &expected_decimal);
  s21_from_float_to_decimal(a, &a_decimal);
  s21_from_float_to_decimal(b, &b_decimal);
  setSignInt(1, &a_decimal);

  int code = s21_mul(a_decimal, b_decimal, &res);
  float got_float = 0;
  s21_from_decimal_to_float(res, &got_float);
  ck_assert_int_eq(code, 0);
  ck_assert_float_eq_tol(got_float, expected, 1e-06);

  expected = (a * (-1)) * (b * (-1));
  s21_from_float_to_decimal(expected, &expected_decimal);
  setSignInt(1, &b_decimal);
  code = s21_mul(a_decimal, b_decimal, &res);
  got_float = 0;
  s21_from_decimal_to_float(res, &got_float);
  ck_assert_int_eq(code, 0);
  ck_assert_float_eq_tol(got_float, expected, 1e-06);

  expected = a * (b * (-1));
  s21_from_float_to_decimal(expected, &expected_decimal);
  setSignInt(1, &b_decimal);
  setSignInt(0, &a_decimal);
  code = s21_mul(a_decimal, b_decimal, &res);
  got_float = 0;
  s21_from_decimal_to_float(res, &got_float);
  ck_assert_int_eq(code, 0);
  ck_assert_float_eq_tol(got_float, expected, 1e-06);
}
END_TEST

START_TEST(test_mul_super_big_number) {
  s21_decimal res = {0};
  s21_decimal expected_decimal = {{0, 0, 0, 0}};
  s21_decimal a_decimal = {{214748363, 214748363, 214748363, 0}};
  s21_decimal b_decimal = {{125, 125, 125, 0}};
  int code = s21_mul(a_decimal, b_decimal, &res);
  ck_assert_int_eq(code, 1);
  ck_assert_int_eq(s21_is_equal(res, expected_decimal), true);

  s21_decimal expected_decimal2 = {{0, 0, 0, 0}};
  s21_decimal a_decimal2 = {{214748363, 214748363, 214748363, 0}};
  s21_decimal b_decimal2 = {{125, 125, 125, 0}};
  setSignInt(1, &a_decimal2);
  code = s21_mul(a_decimal2, b_decimal2, &res);
  ck_assert_int_eq(code, 2);
  ck_assert_int_eq(s21_is_equal(res, expected_decimal2), true);

  s21_decimal expected_decimal3 = {{4294967295, 4294967295, 4294967295, 0}};
  s21_decimal a_decimal3 = {{4294967295, 0, 0, 0}};
  s21_decimal b_decimal3 = {{1, 1, 1, 0}};
  code = s21_mul(a_decimal3, b_decimal3, &res);
  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(s21_is_equal(res, expected_decimal3), true);

  // s21_decimal expected_decimal4 = {{0, 0, 0, 0}};

  s21_decimal a_decimal4 = {{4294967295, 0, 0, (1 << 16)}};
  s21_decimal b_decimal4 = {{2, 2, 10, 0}};
  code = s21_mul(a_decimal4, b_decimal4, &res);
  ck_assert_int_eq(code, 0);
  // ck_assert_int_eq(s21_is_equal(res, expected_decimal4), true);
}
END_TEST

START_TEST(test_max_exp) {
  s21_decimal res = {0};

  s21_decimal expected_decimal = {{0, 0, 0, 0}};
  s21_decimal a_decimal = {{1, 1, 1, (120 << 16)}};
  s21_decimal b_decimal = {{1, 1, 1, (28 << 16)}};  // dddddddddddd
  int code = s21_mul(a_decimal, b_decimal, &res);
  ck_assert_int_eq(code, 1);
  ck_assert_int_eq(s21_is_equal(res, expected_decimal), true);

  s21_decimal expected_decimal2 = {{0, 0, 0, 0}};
  s21_decimal a_decimal2 = {{429496729, 4294967295, 4294967295, 0}};
  s21_decimal b_decimal2 = {{429496729, 429496729, 429496729, 0}};
  setSignInt(1, &a_decimal2);
  code = s21_mul(a_decimal2, b_decimal2, &res);
  ck_assert_int_eq(code, 2);
  ck_assert_int_eq(s21_is_equal(res, expected_decimal2), true);

  s21_decimal expected_decimal3 = {{0, 0, 0, 0}};
  s21_decimal a_decimal3 = {{429496729, 4294967295, 4294967295, (22 << 16)}};
  s21_decimal b_decimal3 = {{429496729, 429496729, 429496729, 0}};
  code = s21_mul(a_decimal3, b_decimal3, &res);
  ck_assert_int_eq(code, 1);
  ck_assert_int_eq(s21_is_equal(res, expected_decimal3), true);
}
END_TEST

Suite *s21_test_mul() {
  Suite *s = NULL;
  TCase *tc_core = NULL;

  s = suite_create("s21_mul");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_mul_positive_int);
  tcase_add_test(tc_core, test_mul_negative_int);
  tcase_add_test(tc_core, test_mul_positive_float);
  tcase_add_test(tc_core, test_mul_negative_float);
  tcase_add_test(tc_core, test_mul_super_big_number);
  tcase_add_test(tc_core, test_max_exp);

  suite_add_tcase(s, tc_core);
  return s;
}