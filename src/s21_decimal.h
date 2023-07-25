#ifndef S21_DECIMAL
#define S21_DECIMAL

#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
//#include <stdlib.h>

#define MINUS 0x80000000
#define PLUS 0xFF0000
#define MAX_DECIMAL powl(2.0, 96)
#define MIN_DECIMAL -1 * powl(2.0, 96)

typedef struct {
  unsigned int bits[4];
} s21_decimal;

typedef struct {
  unsigned int bits[8];
} s21_decimal_big;

// Arithmetic Operators
int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

// Comparison Operators
int s21_is_less(s21_decimal value_1, s21_decimal value_2);
int s21_is_less_or_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_greater(s21_decimal value_1, s21_decimal value_2);
int s21_is_greater_or_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_not_equal(s21_decimal value_1, s21_decimal value_2);

// Convertors and parsers
int s21_from_int_to_decimal(int src, s21_decimal *dst);
int s21_from_float_to_decimal(float src, s21_decimal *dst);
int s21_from_decimal_to_int(s21_decimal src, int *dst);
int s21_from_decimal_to_float(s21_decimal src, float *dst);

// Another functions
int s21_floor(s21_decimal value, s21_decimal *result);
int s21_round(s21_decimal value, s21_decimal *result);
int s21_truncate(s21_decimal value, s21_decimal *result);
int s21_negate(s21_decimal value, s21_decimal *result);

// Helpful functions
int getScale(float src);
s21_decimal setShift(s21_decimal dst, int j);
void get_bits(s21_decimal obj);
int getExp(int bit3);
int setBit(int index, s21_decimal *dst);
int getSignInt(int src);
void setSignInt(int sign, s21_decimal *dst);
int get_bit(s21_decimal value, int i);
s21_decimal add_function(s21_decimal value_1, s21_decimal value_2, int subFlag);
int overflow_check(int bit1, int bit2, int temp);
int overflow_check_big(s21_decimal_big value);
int overflowFix(s21_decimal_big *value);
int big_rounding(s21_decimal_big *value);
void removeBit(int j, s21_decimal *dst);
int normalize(s21_decimal *value_1, s21_decimal *value_2);
s21_decimal sub_function(s21_decimal value_1, s21_decimal value_2);
s21_decimal signLogic(int value_1_sign, int value_2_sign, s21_decimal value_1,
                      s21_decimal value_2, int test);
s21_decimal divLogic(s21_decimal value_1, s21_decimal value_2,
                     s21_decimal *remainder_val);
int isZero(s21_decimal value_1);

// big decimal functions
s21_decimal_big add_function_big(s21_decimal_big value_1,
                                 s21_decimal_big value_2, int subFlag);
s21_decimal_big convertBig(s21_decimal dst);
s21_decimal convertBack(s21_decimal_big dst);
void get_bits_big(s21_decimal_big obj);
int get_bit_big(s21_decimal_big value, int i);
int s21_is_greater_big(s21_decimal_big value_1, s21_decimal_big value_2);
void removeBit_big(int j, s21_decimal_big *dst);
int s21_is_equal_big(s21_decimal_big value_1, s21_decimal_big value_2);
int s21_is_greater_or_equal_big(s21_decimal_big value_1,
                                s21_decimal_big value_2);
int s21_is_less_big(s21_decimal_big value_1, s21_decimal_big value_2);
int nonZeroNumberBig(s21_decimal_big dst);

s21_decimal_big sub_function_big(s21_decimal_big value_1,
                                 s21_decimal_big value_2);
s21_decimal_big setShiftBig(s21_decimal_big dst, int j);
s21_decimal s21_div_part(s21_decimal value_1, s21_decimal value_2,
                         s21_decimal *result);
s21_decimal_big signLogicBig(int value_1_sign, int value_2_sign,
                             s21_decimal_big value_1, s21_decimal_big value_2,
                             int test);
s21_decimal_big divLogicBig(s21_decimal_big value_1, s21_decimal_big value_2,
                            s21_decimal_big *remainder_val);

void sub_sign_chek(int value_1_sign, int value_2_sign, int test,
                   s21_decimal_big value_1, s21_decimal_big value_2,
                   s21_decimal_big *result);

void add_sign_chek(int value_1_sign, int value_2_sign, s21_decimal_big value_1,
                   s21_decimal_big value_2, s21_decimal_big *res_bit);

int s21_add_big(s21_decimal_big value_1, s21_decimal_big value_2,
                s21_decimal_big *result);
int s21_sub_big(s21_decimal_big value_1, s21_decimal_big value_2,
                s21_decimal_big *result);
int s21_mul_big(s21_decimal_big value_1, s21_decimal_big value_2,
                s21_decimal_big *result);
int s21_div_big(s21_decimal_big value_1, s21_decimal_big value_2,
                s21_decimal_big *result);
void setSignIntBig(int sign, s21_decimal_big *dst);
int s21_div_big_ten(s21_decimal_big value_1, s21_decimal_big value_2,
                    s21_decimal_big *result, s21_decimal_big *remainder);
void remainder_def(int result_exp, s21_decimal_big remainder_val,
                   s21_decimal_big value_2, s21_decimal_big *res_big);
int s21_div_big_ten(s21_decimal_big value_1, s21_decimal_big value_2,
                    s21_decimal_big *result, s21_decimal_big *remainder);
int normalize_big(s21_decimal_big *value_1, s21_decimal_big *value_2);
#endif

// Библиотека должна быть разработана на языке Си стандарта C11 с использованием
// компиятора gcc Код библиотеки должен находиться в папке src в ветке develop
// При написании кода необходимо придерживаться Google Style
// Оформить решение как статическую библиотеку (с заголовочным файлом
// s21_decimal.h) Библиотека должна быть разработана в соответствии с принципами
// структурного программирования Перед каждой функцией использовать префикс s21_
// Подготовить полное покрытие unit-тестами функций библиотеки c помощью
// библиотеки Check Unit-тесты должны покрывать не менее 80% каждой функции
// Предусмотреть Makefile для сборки библиотеки и тестов (с целями all, clean,
// test, s21_decimal.a, gcov_report) В цели gcov_report должен формироваться
// отчёт gcov в виде html страницы. Для этого unit-тесты должны запускаться с
// флагами gcov При реализации decimal ориентироваться на двоичное представление
// с целочисленным массивом bits, как указано в примере выше. Соблюсти положение
// разрядов числа в массиве bits

// Запрещено использование типа __int128
// Конечные нули можно как оставлять, так и удалять (за исключением функции
// s21_truncate) Определяемый тип должен поддерживать числа от
// -79,228,162,514,264,337,593,543,950,335 до
// +79,228,162,514,264,337,593,543,950,335.
