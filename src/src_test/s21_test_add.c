#include "s21_test_decimal.h"

START_TEST(test_add_positive_int) {
  srand(time(NULL));
  long long a = random_ll();
  long long b = random_ll();

  long long expected = a + b;
  s21_decimal res = {0};
  s21_decimal expected_decimal = convert_ll_to_decimal(expected);
  s21_decimal a_decimal = convert_ll_to_decimal(a);
  s21_decimal b_decimal = convert_ll_to_decimal(b);

  int code = s21_add(a_decimal, b_decimal, &res);
  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(s21_is_equal(res, expected_decimal), true);
}
END_TEST

START_TEST(test_add_negative_int) {
  srand(time(NULL));
  long long a = random_ll();
  long long b = random_ll();
  long long expected = a + (b * (-1));

  s21_decimal res = {0};
  s21_decimal expected_decimal = convert_ll_to_decimal(expected);
  s21_decimal a_decimal = convert_ll_to_decimal(a);
  s21_decimal b_decimal = convert_ll_to_decimal(b);

  setSignInt(1, &b_decimal);
  int code = s21_add(a_decimal, b_decimal, &res);
  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(s21_is_equal(res, expected_decimal), true);

  setSignInt(0, &b_decimal);
  expected = (a * (-1)) + b;
  expected_decimal = convert_ll_to_decimal(expected);
  setSignInt(1, &a_decimal);
  code = s21_add(a_decimal, b_decimal, &res);
  ck_assert_int_eq(s21_is_equal(res, expected_decimal), true);

  expected = (a * (-1)) + (b * (-1));
  s21_decimal res1 = {0};
  expected_decimal = convert_ll_to_decimal(expected);
  a_decimal = convert_ll_to_decimal(a);
  b_decimal = convert_ll_to_decimal(b);
  setSignInt(1, &a_decimal);
  setSignInt(1, &b_decimal);

  code = s21_add(a_decimal, b_decimal, &res1);
  ck_assert_int_eq(s21_is_equal(res1, expected_decimal), true);
}
END_TEST

START_TEST(overflow_plus) {
  s21_decimal a = {0};
  s21_decimal b = {0};
  s21_decimal res = {0};
  setBit(95, &a);
  setBit(94, &a);
  setBit(95, &b);
  setBit(94, &b);
  int code = s21_add(a, b, &res);
  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(overflow_minus) {
  s21_decimal a = {0};
  s21_decimal b = {0};
  s21_decimal res = {0};
  setBit(95, &a);
  setBit(94, &a);
  setBit(95, &b);
  setBit(94, &b);
  setSignInt(1, &a);
  setSignInt(1, &b);
  int code = s21_add(a, b, &res);
  ck_assert_int_eq(code, 2);
}
END_TEST

START_TEST(test_add_float_plus) {  // ОШИБКА
  srand(time(NULL));
  float a = random_float(0.00, 9000.99999);
  float b = random_float(0.00, 1000.99999);
  float expected = a + b;

  s21_decimal res = {0};
  s21_decimal expected_decimal = {0};
  s21_decimal a_decimal = {0};
  s21_decimal b_decimal = {0};
  s21_from_float_to_decimal(expected, &expected_decimal);
  s21_from_float_to_decimal(a, &a_decimal);
  s21_from_float_to_decimal(b, &b_decimal);

  int code = s21_add(a_decimal, b_decimal, &res);
  float got_float = 0;
  s21_from_decimal_to_float(res, &got_float);
  ck_assert_int_eq(code, 0);
  ck_assert_float_eq_tol(got_float, expected, 1e-06);
}
END_TEST

START_TEST(test_add_float_minus) {  ///ОШИБКА
  srand(time(NULL));
  float a = random_float(0.00, 9000.99999) * -1;
  float b = random_float(0.00, 1000.99999) * -1;
  float expected = a + b;

  s21_decimal res = {0};
  s21_decimal expected_decimal = {0};
  s21_decimal a_decimal = {0};
  s21_decimal b_decimal = {0};
  s21_from_float_to_decimal(expected, &expected_decimal);
  s21_from_float_to_decimal(a, &a_decimal);
  s21_from_float_to_decimal(b, &b_decimal);

  int code = s21_add(a_decimal, b_decimal, &res);
  float got_float = 0;
  s21_from_decimal_to_float(res, &got_float);
  ck_assert_int_eq(code, 0);
  ck_assert_float_eq_tol(got_float, expected, 1e-06);
}
END_TEST

START_TEST(test_add_float_random_sign) {
  srand(time(NULL));
  float a = random_float(-9000.99999, 9000.99999) * -1;
  float b = random_float(-9000.99999, 1000.99999) * -1;
  float expected = a + b;

  s21_decimal res = {0};
  s21_decimal expected_decimal = {0};
  s21_decimal a_decimal = {0};
  s21_decimal b_decimal = {0};
  s21_from_float_to_decimal(expected, &expected_decimal);
  s21_from_float_to_decimal(a, &a_decimal);
  s21_from_float_to_decimal(b, &b_decimal);

  int code = s21_add(a_decimal, b_decimal, &res);
  float got_float = 0;
  s21_from_decimal_to_float(res, &got_float);
  ck_assert_int_eq(code, 0);
  ck_assert_float_eq_tol(got_float, expected, 1e-06);
}
END_TEST

START_TEST(test_add_super_big_number) {
  s21_decimal res = {0};
  s21_decimal expected_decimal = {{214748488, 214748488, 214748488, 0}};
  s21_decimal a_decimal = {{214748363, 214748363, 214748363, 0}};
  s21_decimal b_decimal = {{125, 125, 125, 0}};
  int code = s21_add(a_decimal, b_decimal, &res);
  code = code;
  ck_assert_int_eq(s21_is_equal(res, expected_decimal), true);

  s21_decimal expected_decimal2 = {{124, 126, 125, 0}};
  s21_decimal a_decimal2 = {{4294967295, 0, 0, 0}};
  s21_decimal b_decimal2 = {{125, 125, 125, 0}};
  code = s21_add(a_decimal2, b_decimal2, &res);
  code = code;
  ck_assert_int_eq(s21_is_equal(res, expected_decimal2), true);

  s21_decimal expected_decimal3 = {{125, 124, 126, 0}};
  s21_decimal a_decimal3 = {{0, 4294967295, 0, 0}};
  s21_decimal b_decimal3 = {{125, 125, 125, 0}};
  code = s21_add(a_decimal3, b_decimal3, &res);
  code = code;
  ck_assert_int_eq(s21_is_equal(res, expected_decimal3), true);
}
END_TEST

START_TEST(test_add_exp_test) {
  s21_decimal res = {0};
  s21_decimal expected_decimal = {{2205, 0, 0, (2 << 16)}};
  s21_decimal a_decimal = {{1205, 0, 0, (2 << 16)}};
  s21_decimal b_decimal = {{100, 0, 0, (1 << 16)}};
  int code = s21_add(a_decimal, b_decimal, &res);
  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(s21_is_equal(res, expected_decimal), true);

  s21_decimal expected_decimal2 = {{0, 500987654, 0, (8 << 16)}};
  s21_decimal a_decimal2 = {{0, 5000, 0, (3 << 16)}};
  s21_decimal b_decimal2 = {{0, 987654, 0, (8 << 16)}};
  code = s21_add(a_decimal2, b_decimal2, &res);
  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(s21_is_equal(res, expected_decimal2), true);

  s21_decimal expected_decimal3 = {{0, 938447366, 1164153, (16 << 16)}};
  s21_decimal a_decimal3 = {{0, 5000, 0, (4 << 16)}};
  s21_decimal b_decimal3 = {{0, 987654, 0, (16 << 16)}};
  code = s21_add(a_decimal3, b_decimal3, &res);
  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(s21_is_equal(res, expected_decimal3), true);

  s21_decimal expected_decimal4 = {{3476291584, 4046263891, 6702604, (28 << 16)}};
  s21_decimal a_decimal4 = {{123456789, 0, 0, (10 << 16)}};
  s21_decimal b_decimal4 = {{0, 0, 9999, (28 << 16)}};
  code = s21_add(a_decimal4, b_decimal4, &res);
  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(s21_is_equal(res, expected_decimal4), true);


  s21_decimal expected_decimal5 = {{0, 2147483648, 429496739, (9 << 16)}};
  s21_decimal a_decimal5 = {{0, 0, 4294967295, (10 << 16)}};
  s21_decimal b_decimal5 = {{0, 0, 100, (10 << 16)}};
  code = s21_add(a_decimal5, b_decimal5, &res);
  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(s21_is_equal(res, expected_decimal5), true);
  // s21_decimal expected_decimal5 = {0, 0, 0, 0};
  // s21_decimal a_decimal5 = {4294967295, 4294967295, 4294967295, (0 << 16)};
  // s21_decimal b_decimal5 = {4294967295, 4294967295, 4294967295, (28 << 16)};
  // code = s21_add(a_decimal5, b_decimal5, &res);
  // ck_assert_int_eq(code, 1);
  // ck_assert_int_eq(s21_is_equal(res, expected_decimal5), true);
}
END_TEST

START_TEST(weird_normalize_behavior) {
  weird_normalize_behavior = weird_normalize_behavior;
  s21_decimal val_1 = {{4294967295, 4294967295, 4294967295, 0}};
  s21_decimal val_2 = {{12345, 0, 0, 5 << 15}};
  s21_decimal res = {0};
  s21_add(val_1, val_2, &res);
  
  s21_decimal val_1_test_2 = {{4294967295, 4294967295, 42949672, 0}};
  s21_decimal val_2_test_2 = {{12345, 0, 0, 5 << 15}};
  s21_decimal res_2 = {0};
  s21_add(val_1_test_2, val_2_test_2, &res_2);
}
END_TEST

Suite *s21_test_add() {
  Suite *s = NULL;
  TCase *tc_core = NULL;

  s = suite_create("s21_add");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_add_positive_int);
  tcase_add_test(tc_core, test_add_negative_int);
  tcase_add_test(tc_core, overflow_plus);
  tcase_add_test(tc_core, overflow_minus);
  tcase_add_test(tc_core, test_add_float_plus);
  tcase_add_test(tc_core, test_add_float_minus);
  tcase_add_test(tc_core, test_add_float_random_sign);
  tcase_add_test(tc_core, test_add_super_big_number);
  tcase_add_test(tc_core, test_add_exp_test);
  // tcase_add_test(tc_core, weird_normalize_behavior);
  suite_add_tcase(s, tc_core);
  return s;
}
