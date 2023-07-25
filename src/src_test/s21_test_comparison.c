#include "s21_test_decimal.h"

START_TEST(test_comparison_positives_int) {
  s21_decimal val_1 = {{123, 0, 0, 0}};
  s21_decimal val_2 = {{0, 1, 0, 0}};
  ck_assert(s21_is_less(val_2, val_1) == 0);
  ck_assert(s21_is_less(val_1, val_2) == 1);
  ck_assert(s21_is_greater(val_2, val_1) == 1);
  ck_assert(s21_is_greater(val_1, val_2) == 0);
  ck_assert(s21_is_less_or_equal(val_1, val_2) == 1);
  ck_assert(s21_is_less_or_equal(val_2, val_1) == 0);
  ck_assert(s21_is_greater_or_equal(val_1, val_2) == 0);
  ck_assert(s21_is_greater_or_equal(val_2, val_1) == 1);
  ck_assert(s21_is_equal(val_1, val_2) == 0);
  ck_assert(s21_is_not_equal(val_1, val_2) == 1);
  val_1.bits[1] = 1;
  val_2.bits[0] = 123;
  ck_assert(s21_is_less_or_equal(val_1, val_2) == 1);
  ck_assert(s21_is_less_or_equal(val_2, val_1) == 1);
  ck_assert(s21_is_greater_or_equal(val_1, val_2) == 1);
  ck_assert(s21_is_greater_or_equal(val_2, val_1) == 1);
  ck_assert(s21_is_equal(val_1, val_2) == 1);
  ck_assert(s21_is_equal(val_2, val_1) == 1);
  ck_assert(s21_is_not_equal(val_1, val_2) == 0);
  ck_assert(s21_is_not_equal(val_2, val_1) == 0);
}
END_TEST

START_TEST(test_comparison_negatives_int) {
  s21_decimal val_1 = {{123, 0, 0, 1 << 31}};
  s21_decimal val_2 = {{0, 1, 0, 1 << 31}};
  ck_assert(s21_is_less(val_2, val_1) == 1);
  ck_assert(s21_is_less(val_1, val_2) == 0);
  ck_assert(s21_is_greater(val_2, val_1) == 0);
  ck_assert(s21_is_greater(val_1, val_2) == 1);
  ck_assert(s21_is_less_or_equal(val_1, val_2) == 0);
  ck_assert(s21_is_less_or_equal(val_2, val_1) == 1);
  ck_assert(s21_is_greater_or_equal(val_1, val_2) == 1);
  ck_assert(s21_is_greater_or_equal(val_2, val_1) == 0);
  ck_assert(s21_is_equal(val_1, val_2) == 0);
  ck_assert(s21_is_not_equal(val_1, val_2) == 1);
  val_1.bits[1] = 1;
  val_2.bits[0] = 123;
  ck_assert(s21_is_less_or_equal(val_1, val_2) == 1);
  ck_assert(s21_is_less_or_equal(val_2, val_1) == 1);
  ck_assert(s21_is_greater_or_equal(val_1, val_2) == 1);
  ck_assert(s21_is_greater_or_equal(val_2, val_1) == 1);
  ck_assert(s21_is_equal(val_1, val_2) == 1);
  ck_assert(s21_is_equal(val_2, val_1) == 1);
  ck_assert(s21_is_not_equal(val_1, val_2) == 0);
  ck_assert(s21_is_not_equal(val_2, val_1) == 0);
}
END_TEST

START_TEST(test_comparison_combine_int_1) {
  s21_decimal val_1 = {{123, 0, 0, 1 << 31}};
  s21_decimal val_2 = {{0, 1, 0, 0}};
  ck_assert(s21_is_less(val_2, val_1) == 0);
  ck_assert(s21_is_less(val_1, val_2) == 1);
  ck_assert(s21_is_greater(val_2, val_1) == 1);
  ck_assert(s21_is_greater(val_1, val_2) == 0);
  ck_assert(s21_is_less_or_equal(val_1, val_2) == 1);
  ck_assert(s21_is_less_or_equal(val_2, val_1) == 0);
  ck_assert(s21_is_greater_or_equal(val_1, val_2) == 0);
  ck_assert(s21_is_greater_or_equal(val_2, val_1) == 1);
  ck_assert(s21_is_equal(val_1, val_2) == 0);
  ck_assert(s21_is_not_equal(val_1, val_2) == 1);
  val_1.bits[1] = 1;
  val_2.bits[0] = 123;
  ck_assert(s21_is_less_or_equal(val_1, val_2) == 1);
  ck_assert(s21_is_less_or_equal(val_2, val_1) == 0);
  ck_assert(s21_is_greater_or_equal(val_1, val_2) == 0);
  ck_assert(s21_is_greater_or_equal(val_2, val_1) == 1);
  ck_assert(s21_is_equal(val_1, val_2) == 0);
  ck_assert(s21_is_equal(val_2, val_1) == 0);
  ck_assert(s21_is_not_equal(val_1, val_2) == 1);
  ck_assert(s21_is_not_equal(val_2, val_1) == 1);
}
END_TEST

START_TEST(test_comparison_combine_int_2) {
  s21_decimal val_1 = {{123, 0, 0, 0}};
  s21_decimal val_2 = {{0, 1, 0, 1 << 31}};
  ck_assert(s21_is_less(val_2, val_1) == 1);
  ck_assert(s21_is_less(val_1, val_2) == 0);
  ck_assert(s21_is_greater(val_2, val_1) == 0);
  ck_assert(s21_is_greater(val_1, val_2) == 1);
  ck_assert(s21_is_less_or_equal(val_1, val_2) == 0);
  ck_assert(s21_is_less_or_equal(val_2, val_1) == 1);
  ck_assert(s21_is_greater_or_equal(val_1, val_2) == 1);
  ck_assert(s21_is_greater_or_equal(val_2, val_1) == 0);
  ck_assert(s21_is_equal(val_1, val_2) == 0);
  ck_assert(s21_is_not_equal(val_1, val_2) == 1);
  val_1.bits[1] = 1;
  val_2.bits[0] = 123;
  ck_assert(s21_is_less_or_equal(val_1, val_2) == 0);
  ck_assert(s21_is_less_or_equal(val_2, val_1) == 1);
  ck_assert(s21_is_greater_or_equal(val_1, val_2) == 1);
  ck_assert(s21_is_greater_or_equal(val_2, val_1) == 0);
  ck_assert(s21_is_equal(val_1, val_2) == 0);
  ck_assert(s21_is_equal(val_2, val_1) == 0);
  ck_assert(s21_is_not_equal(val_1, val_2) == 1);
  ck_assert(s21_is_not_equal(val_2, val_1) == 1);
}
END_TEST

START_TEST(test_comparison_positives_float_int) {
  s21_decimal val_1 = {{123, 0, 0, 3 << 16}};
  s21_decimal val_2 = {{0, 1, 0, 0}};
  ck_assert(s21_is_less(val_2, val_1) == 0);
  ck_assert(s21_is_less(val_1, val_2) == 1);
  ck_assert(s21_is_greater(val_2, val_1) == 1);
  ck_assert(s21_is_greater(val_1, val_2) == 0);
  ck_assert(s21_is_less_or_equal(val_1, val_2) == 1);
  ck_assert(s21_is_less_or_equal(val_2, val_1) == 0);
  ck_assert(s21_is_greater_or_equal(val_1, val_2) == 0);
  ck_assert(s21_is_greater_or_equal(val_2, val_1) == 1);
  ck_assert(s21_is_equal(val_1, val_2) == 0);
  ck_assert(s21_is_not_equal(val_1, val_2) == 1);
  val_1.bits[1] = 1;
  val_2.bits[0] = 123;
  ck_assert(s21_is_less_or_equal(val_1, val_2) == 1);
  ck_assert(s21_is_less_or_equal(val_2, val_1) == 0);
  ck_assert(s21_is_greater_or_equal(val_1, val_2) == 0);
  ck_assert(s21_is_greater_or_equal(val_2, val_1) == 1);
  ck_assert(s21_is_equal(val_1, val_2) == 0);
  ck_assert(s21_is_equal(val_2, val_1) == 0);
  ck_assert(s21_is_not_equal(val_1, val_2) == 1);
  ck_assert(s21_is_not_equal(val_2, val_1) == 1);
}
END_TEST

START_TEST(test_comparison_positives_int_float) {
  s21_decimal val_1 = {{123, 0, 0, 0}};
  s21_decimal val_2 = {{124, 0, 0, 1 << 16}};
  ck_assert(s21_is_less(val_2, val_1) == 1);
  ck_assert(s21_is_less(val_1, val_2) == 0);
  ck_assert(s21_is_greater(val_2, val_1) == 0);
  ck_assert(s21_is_greater(val_1, val_2) == 1);
  ck_assert(s21_is_less_or_equal(val_1, val_2) == 0);
  ck_assert(s21_is_less_or_equal(val_2, val_1) == 1);
  ck_assert(s21_is_greater_or_equal(val_1, val_2) == 1);
  ck_assert(s21_is_greater_or_equal(val_2, val_1) == 0);
  ck_assert(s21_is_equal(val_1, val_2) == 0);
  ck_assert(s21_is_not_equal(val_1, val_2) == 1);
  val_1.bits[0] = 124;
  ck_assert(s21_is_less_or_equal(val_1, val_2) == 0);
  ck_assert(s21_is_less_or_equal(val_2, val_1) == 1);
  ck_assert(s21_is_greater_or_equal(val_1, val_2) == 1);
  ck_assert(s21_is_greater_or_equal(val_2, val_1) == 0);
  ck_assert(s21_is_equal(val_1, val_2) == 0);
  ck_assert(s21_is_equal(val_2, val_1) == 0);
  ck_assert(s21_is_not_equal(val_1, val_2) == 1);
  ck_assert(s21_is_not_equal(val_2, val_1) == 1);
}
END_TEST

START_TEST(test_comparison_positives_float_float) {
  s21_decimal val_1 = {{123, 0, 0, 1 << 16}};
  s21_decimal val_2 = {{124, 0, 0, 1 << 16}};
  ck_assert(s21_is_less(val_2, val_1) == 0);
  ck_assert(s21_is_less(val_1, val_2) == 1);
  ck_assert(s21_is_greater(val_2, val_1) == 1);
  ck_assert(s21_is_greater(val_1, val_2) == 0);
  ck_assert(s21_is_less_or_equal(val_1, val_2) == 1);
  ck_assert(s21_is_less_or_equal(val_2, val_1) == 0);
  ck_assert(s21_is_greater_or_equal(val_1, val_2) == 0);
  ck_assert(s21_is_greater_or_equal(val_2, val_1) == 1);
  ck_assert(s21_is_equal(val_1, val_2) == 0);
  ck_assert(s21_is_not_equal(val_1, val_2) == 1);
  val_1.bits[0] = 124;
  ck_assert(s21_is_less_or_equal(val_1, val_2) == 1);
  ck_assert(s21_is_less_or_equal(val_2, val_1) == 1);
  ck_assert(s21_is_greater_or_equal(val_1, val_2) == 1);
  ck_assert(s21_is_greater_or_equal(val_2, val_1) == 1);
  ck_assert(s21_is_equal(val_1, val_2) == 1);
  ck_assert(s21_is_equal(val_2, val_1) == 1);
  ck_assert(s21_is_not_equal(val_1, val_2) == 0);
  ck_assert(s21_is_not_equal(val_2, val_1) == 0);
}
END_TEST

START_TEST(test_comparison_negatives_float_int) {
  s21_decimal val_1 = {{123, 0, 0, (1 << 31) + (3 << 16)}};
  s21_decimal val_2 = {{0, 1, 0, 0}};
  ck_assert(s21_is_less(val_2, val_1) == 0);
  ck_assert(s21_is_less(val_1, val_2) == 1);
  ck_assert(s21_is_greater(val_2, val_1) == 1);
  ck_assert(s21_is_greater(val_1, val_2) == 0);
  ck_assert(s21_is_less_or_equal(val_1, val_2) == 1);
  ck_assert(s21_is_less_or_equal(val_2, val_1) == 0);
  ck_assert(s21_is_greater_or_equal(val_1, val_2) == 0);
  ck_assert(s21_is_greater_or_equal(val_2, val_1) == 1);
  ck_assert(s21_is_equal(val_1, val_2) == 0);
  ck_assert(s21_is_not_equal(val_1, val_2) == 1);
  val_1.bits[1] = 1;
  val_2.bits[0] = 123;
  ck_assert(s21_is_less_or_equal(val_1, val_2) == 1);
  ck_assert(s21_is_less_or_equal(val_2, val_1) == 0);
  ck_assert(s21_is_greater_or_equal(val_1, val_2) == 0);
  ck_assert(s21_is_greater_or_equal(val_2, val_1) == 1);
  ck_assert(s21_is_equal(val_1, val_2) == 0);
  ck_assert(s21_is_equal(val_2, val_1) == 0);
  ck_assert(s21_is_not_equal(val_1, val_2) == 1);
  ck_assert(s21_is_not_equal(val_2, val_1) == 1);
}
END_TEST

START_TEST(test_comparison_negatives_int_float) {
  s21_decimal val_1 = {{123, 0, 0, 0}};
  s21_decimal val_2 = {{124, 0, 0, (1 << 31) + (3 << 16)}};
  ck_assert(s21_is_less(val_2, val_1) == 1);
  ck_assert(s21_is_less(val_1, val_2) == 0);
  ck_assert(s21_is_greater(val_2, val_1) == 0);
  ck_assert(s21_is_greater(val_1, val_2) == 1);
  ck_assert(s21_is_less_or_equal(val_1, val_2) == 0);
  ck_assert(s21_is_less_or_equal(val_2, val_1) == 1);
  ck_assert(s21_is_greater_or_equal(val_1, val_2) == 1);
  ck_assert(s21_is_greater_or_equal(val_2, val_1) == 0);
  ck_assert(s21_is_equal(val_1, val_2) == 0);
  ck_assert(s21_is_not_equal(val_1, val_2) == 1);
  val_1.bits[0] = 124;
  ck_assert(s21_is_less_or_equal(val_1, val_2) == 0);
  ck_assert(s21_is_less_or_equal(val_2, val_1) == 1);
  ck_assert(s21_is_greater_or_equal(val_1, val_2) == 1);
  ck_assert(s21_is_greater_or_equal(val_2, val_1) == 0);
  ck_assert(s21_is_equal(val_1, val_2) == 0);
  ck_assert(s21_is_equal(val_2, val_1) == 0);
  ck_assert(s21_is_not_equal(val_1, val_2) == 1);
  ck_assert(s21_is_not_equal(val_2, val_1) == 1);
}
END_TEST

START_TEST(test_comparison_negatives_float_float) {
  s21_decimal val_1 = {{123, 0, 0, (1 << 31) + (3 << 16)}};
  s21_decimal val_2 = {{124, 0, 0, (1 << 31) + (3 << 16)}};
  ck_assert(s21_is_less(val_2, val_1) == 1);
  ck_assert(s21_is_less(val_1, val_2) == 0);
  ck_assert(s21_is_greater(val_2, val_1) == 0);
  ck_assert(s21_is_greater(val_1, val_2) == 1);
  ck_assert(s21_is_less_or_equal(val_1, val_2) == 0);
  ck_assert(s21_is_less_or_equal(val_2, val_1) == 1);
  ck_assert(s21_is_greater_or_equal(val_1, val_2) == 1);
  ck_assert(s21_is_greater_or_equal(val_2, val_1) == 0);
  ck_assert(s21_is_equal(val_1, val_2) == 0);
  ck_assert(s21_is_not_equal(val_1, val_2) == 1);
  val_1.bits[0] = 124;
  ck_assert(s21_is_less_or_equal(val_1, val_2) == 1);
  ck_assert(s21_is_less_or_equal(val_2, val_1) == 1);
  ck_assert(s21_is_greater_or_equal(val_1, val_2) == 1);
  ck_assert(s21_is_greater_or_equal(val_2, val_1) == 1);
  ck_assert(s21_is_equal(val_1, val_2) == 1);
  ck_assert(s21_is_equal(val_2, val_1) == 1);
  ck_assert(s21_is_not_equal(val_1, val_2) == 0);
  ck_assert(s21_is_not_equal(val_2, val_1) == 0);
}
END_TEST

START_TEST(test_comparison_weird_cases) {
  s21_decimal val_1 = {{4294967295, 4294967295, 4294967295, 3 << 16}};
  s21_decimal val_2 = {{4294967295, 4294967295, 4294967295, 6 << 16}};
  ck_assert(s21_is_equal(val_1, val_2) == 0);
}
END_TEST

START_TEST(test_comparison_zero) {
  s21_decimal val_1 = {{0, 0, 0, 0}};
  s21_decimal val_2 = {{0, 0, 0, 1 << 31}};
  ck_assert(s21_is_equal(val_1, val_2) == 1);
}

START_TEST(test_comparison_no_exp) {
  s21_decimal val_1 = {{1, 2, 3, 0}};
  s21_decimal val_2 = {{3, 2, 1, 0}};
  ck_assert(s21_is_equal(val_1, val_2) == 0);
}

START_TEST(test_comparison_normalize) {
  s21_decimal val_1 = {{1230, 0, 0, 1 << 16}};
  s21_decimal val_2 = {{123, 0, 0, 0}};
  ck_assert(s21_is_equal(val_1, val_2) == 1);
}

Suite *s21_test_comparison() {
  Suite *s = NULL;
  TCase *tc_core = NULL;

  s = suite_create("s21_comparison");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_comparison_positives_int);
  tcase_add_test(tc_core, test_comparison_negatives_int);
  tcase_add_test(tc_core, test_comparison_combine_int_1);
  tcase_add_test(tc_core, test_comparison_combine_int_2);
  tcase_add_test(tc_core, test_comparison_positives_float_int);
  tcase_add_test(tc_core, test_comparison_positives_int_float);
  tcase_add_test(tc_core, test_comparison_positives_float_float);
  tcase_add_test(tc_core, test_comparison_negatives_float_int);
  tcase_add_test(tc_core, test_comparison_negatives_int_float);
  tcase_add_test(tc_core, test_comparison_negatives_float_float);
  tcase_add_test(tc_core, test_comparison_weird_cases);
  tcase_add_test(tc_core, test_comparison_no_exp);
  tcase_add_test(tc_core, test_comparison_zero);
  tcase_add_test(tc_core, test_comparison_normalize);
  suite_add_tcase(s, tc_core);
  return s;
}
