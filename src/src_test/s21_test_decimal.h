#ifndef S21_TEST_DECIMAL
#define S21_TEST_DECIMAL

#include <check.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#include "../s21_decimal.h"

#define S21_NAN 0. / 0.

Suite* s21_test_add();
Suite* s21_test_sub();
Suite* s21_test_mul();
Suite* s21_test_div();
Suite* s21_test_comparison();
Suite* s21_test_convertors();
Suite* s21_test_another_funct();
//Остальные добавлять по аналогии

void run_test();
s21_decimal convert_ll_to_decimal(long long val);
long long random_ll();
float random_float(float min, float max);

#endif
