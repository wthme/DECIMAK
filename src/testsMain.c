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
  // printf("______CONVERTORS______\n\n");
  // printf("____int_to_decimal____\n\n");
  // s21_decimal res = {0};
  // int_to_decimal_test(res, 1234567);
  // int_to_decimal_test(res, -76543);
  // int_to_decimal_test(res, 4294967295);
  // printf("___float_to_decimal__\n\n");
  // float_to_decimal_test(res, 12345.678);
  // float_to_decimal_test(res, -678.123);
  // float_to_decimal_test(res, 12345.67812312);
  // float_to_decimal_test(res, 12345678.12345678);
  // printf("___decimal_to_int___\n\n");
  // int x = 0;
  // s21_decimal res2 = {1234567, 0, 0, 0};
  // decimal_to_int_test(res2, x);
  // res2.bits[0] = 7654321;
  // decimal_to_int_test(res2, x);
  // res2.bits[3] = 2147483648;
  // decimal_to_int_test(res2, x);
  // res2.bits[0] = 2147483645;
  // decimal_to_int_test(res2, x);
  // res2.bits[3] = 196608;
  // decimal_to_int_test(res2, x);
  // res2.bits[3] = 2147680256;
  // decimal_to_int_test(res2, x);
  // printf("__decimal_to_float__\n\n");
  // float y = 0;
  // s21_decimal res3 = {1234567, 0, 0, 196608};
  // decimal_to_float_test(res3, y);
  // res3.bits[3] = 2147680256;
  // decimal_to_float_test(res3, y);
  // res3.bits[3] = 0;
  // decimal_to_float_test(res3, y);
  // printf("\n______COMPARISON______\n\n");
  // printf("\n_______is_less________\n\n");
  // s21_decimal less1 = {1234567, 0, 0, 0};
  // s21_decimal less2 = {7654321, 0, 0, 0};
  // is_less_test(less1, less2);
  // less2.bits[3] = MINUS;
  // is_less_test(less1, less2);
  // less2.bits[3] = 196608;
  // is_less_test(less1, less2);
  // less2.bits[0] = 1234567;
  // is_less_test(less1, less2);
  // less1.bits[3] = MINUS;
  // is_less_test(less1, less2);
  // printf("\n______is_greater_____\n\n");
  // s21_decimal great1 = {1234567, 0, 0, 0};
  // s21_decimal great2 = {7654321, 0, 0, 0};
  // is_greater_test(great1, great2);
  // great2.bits[3] = MINUS;
  // is_greater_test(great1, great2);
  // great2.bits[3] = 196608;
  // is_greater_test(great1, great2);
  // great2.bits[0] = 1234567;
  // is_greater_test(great1, great2);
  // great1.bits[3] = MINUS;
  // is_greater_test(great1, great2);
  // printf("\n________is_eq_______\n\n");
  // s21_decimal eq1 = {123, 0, 0, 0};
  // s21_decimal eq2 = {123, 0, 0, 0};
  // is_eq_test(eq1, eq2);
  // eq1.bits[0] = 1230;
  // eq1.bits[3] = 65536;
  // is_eq_test(eq1, eq2);
  // eq1.bits[3] = MINUS;
  // is_eq_test(eq1, eq2);
  printf("\n____ARITHMETICS____\n\n");
  printf("\n_______add_________\n\n");

  s21_decimal add1 = {{3294967295, 3294967295, 3294967111, 0}};
  s21_decimal add2 = {{4294967295, 4294967295, 4294967295, 0}};
  // add_test(add1, add2);
  // printf("\n");
  // get_bits(add1);
  printf("\n");
  // add_test(add1, add2);
  // add1.bits[1] = 3;
  // add2.bits[1] = 5;
  // add1.bits[2] = 15;
  // add2.bits[2] = 2;
  // add_test(add1, add2);
  // add1.bits[3] = (4 << 16);
  // add_test(add1, add2);
  // add1.bits[3] |= MINUS;
  // add_test(add1, add2);
  add2.bits[3] = (5 << 16);
  add1.bits[3] = (5 << 16);
  // add1.bits[3] = (28 << 16);
  printf("\n");
  get_bits(add2);
  printf("\n");
  add_test(add1, add2);
  add1.bits[3] |= MINUS;
  // add_test(add1, add2);
  printf("\n_______sub_________\n\n");
  s21_decimal sub1 = {{123, 0, 0, 0}};
  s21_decimal sub2 = {{421, 0, 0, 0}};
  sub_test(sub1, sub2);
  sub1.bits[3] |= MINUS;
  sub_test(sub1, sub2);
  sub1.bits[3] = 0;
  sub1.bits[0] = 421;
  sub2.bits[0] = 123;
  sub_test(sub1, sub2);
  sub1.bits[3] = (1 << 16);
  sub_test(sub1, sub2);
  sub1.bits[3] |= MINUS;
  sub_test(sub1, sub2);
  sub1.bits[1] = 5;
  sub2.bits[1] = 3;
  sub1.bits[2] = 15;
  sub2.bits[2] = 2;
  sub_test(sub1, sub2);
  sub1.bits[3] = (3 << 16);
  // sub_test(sub1, sub2); overflow?
  sub1.bits[3] |= MINUS;
  sub_test(sub1, sub2);
  sub2.bits[3] = sub1.bits[3];
  sub1.bits[3] = 0;
  sub_test(sub1, sub2);
  sub1.bits[3] |= MINUS;
  sub1.bits[0] = 123;
  sub2.bits[0] = 421;
  sub_test(sub1, sub2);
  sub1.bits[3] = 131072;
  sub_test(sub1, sub2);
  sub_test(sub1, sub2);  // overflow?

  // printf("\n ___________MUL TEST___________ \n");
  // s21_decimal mul1 = {25, 5, 0, 1};
  // s21_decimal mul2 = {35, 0, 0, 1};
  // mul_test(mul1, mul2);
  // mul1.bits[2] = 0;
  // mul1.bits[0] = 125;
  // mul_test(mul1, mul2);
  // mul2.bits[0] = 100;
  // mul1.bits[0] = 1000;
  // mul_test(mul1, mul2);
  // mul1.bits[0] = 191567121;
  // mul_test(mul1, mul2);
  // mul1.bits[0] = 0;
  // mul2.bits[0] = 0;
  // mul1.bits[0] = 4294967295;
  // mul2.bits[0] = 4294967295;
  // mul_test(mul1, mul2);
  // mul1.bits[0] = 0;
  // mul2.bits[0] = 0;
  // mul1.bits[1] = 4294967295;
  // mul2.bits[0] = 4294967295;
  // printf("\n ___________div TEST___________ \n");
  // s21_decimal div1 = {1024, 1024, 0, 0};
  // s21_decimal div2 = {10, 0, 0, 0};
  // div_test(div1, div2);
  // div1.bits[0] = 1000;
  // div1.bits[1] = 0;
  // div2.bits[0] = 5;
  // div2.bits[1] = 0;
  // div_test(div1, div2);
  // div1.bits[0] = 0;
  // div1.bits[1] = 0;
  // div1.bits[2] = 345;
  // div2.bits[0] = 2;
  // div2.bits[1] = 0;
  // div_test(div1, div2);

  // printf("\n\n\n ___________TEST BIG DECIMAL___________\n\n\n");
  // s21_decimal_big add11 = {25, 0, 0, 4294967295, 0, 0, 4294967200, 0};
  // s21_decimal_big add22 = {0, 0, 0, 100, 0, 0, 90, 0};
  // add_test_big(add11, add22);
  // add11.bits[0] = 0;
  // add_test_big(add11, add22);
  // add11.bits[0] = 4294967295;
  // add11.bits[1] = 4294967295;
  // add11.bits[2] = 4294967295;
  // add11.bits[3] = 4294967295;
  // add_test_big(add11, add22);
  // add11.bits[0] = 430;
  // add11.bits[1] = 22;
  // add11.bits[2] = 5;
  // add22.bits[0] = 429;
  // add22.bits[1] = 12;
  // add22.bits[2] = 5;
  // // add_test_big(add11, add22);
  // add11.bits[7] |= MINUS;
  // // add_test_big(add11, add22);
  // add11.bits[0] = 4294967295;
  // add11.bits[1] = 4294967295;
  // add11.bits[2] = 4294967295;
  // add22.bits[0] = 4294967295;
  // add22.bits[1] = 4294967295;
  // add22.bits[2] = 4294967295;
  // // add_test_big(add11, add22);
  // add22.bits[7] |= MINUS;
  // add11.bits[0] = 4294967294;
  // // add_test_big(add11, add22);
  // add11.bits[7] = 0;
  // add11.bits[0] = 50;
  // add11.bits[1] = 0;
  // add11.bits[2] = 0;
  // add22.bits[0] = 30;
  // add22.bits[1] = 0;
  // add22.bits[2] = 0;
  // // add_test_big(add11, add22);

  // printf("\n---------SUB----------\n\n");
  // s21_decimal_big sub11 = {29, 1, 4294967291, 0, 0, 0, 0, 0};
  // s21_decimal_big sub22 = {25, 0, 429496729, 0, 0, 0, 0, 0};
  // sub_test_big(sub11, sub22);
  // sub11.bits[7] |= MINUS;
  // sub_test_big(sub11, sub22);
  // sub22.bits[7] |= MINUS;
  // sub_test_big(sub11, sub22);
  // sub11.bits[0] = 4294967295;
  // sub11.bits[1] = 4294967295;
  // sub11.bits[2] = 4294967295;
  // sub22.bits[0] = 4294967295;
  // sub22.bits[1] = 4294967295;
  // sub22.bits[2] = 4294967295;
  // sub_test_big(sub11, sub22);
  // sub22.bits[7] = 0;
  // sub_test_big(sub11, sub22);
  // sub11.bits[7] = 0;
  // sub_test_big(sub11, sub22);
  // sub22.bits[7] |= MINUS;
  // sub_test_big(sub11, sub22);
  // sub11.bits[7] = 0;
  // sub22.bits[7] = 0;
  // sub11.bits[0] = 50;
  // sub11.bits[1] = 0;
  // sub11.bits[2] = 0;
  // sub22.bits[0] = 30;
  // sub22.bits[1] = 0;
  // sub22.bits[2] = 0;
  // sub_test_big(sub11, sub22);
  // sub11.bits[7] |= MINUS;
  // sub_test_big(sub11, sub22);
  // sub11.bits[7] = 0;
  // sub11.bits[0] = 30;
  // sub22.bits[0] = 50;
  // sub_test_big(sub11, sub22);
  // sub22.bits[7] |= MINUS;
  // sub_test_big(sub11, sub22);
  // sub11.bits[7] |= MINUS;
  // sub_test_big(sub11, sub22);

  // sub11.bits[7] = 0;
  // sub22.bits[7] = 0;
  // sub11.bits[0] = 0;
  // sub11.bits[1] = 0;
  // sub11.bits[2] = 0;
  // sub22.bits[0] = 0;
  // sub22.bits[1] = 0;
  // sub22.bits[2] = 0;

  // sub11.bits[3] = 2204967295;
  // sub22.bits[3] = 100;
  // sub_test_big(sub11, sub22);

  // printf("\n---------MUL-----------\n");
  // s21_decimal_big mul11 = {10, 5, 5, 0, 0, 0, 0, 0};
  // s21_decimal_big mul22 = {0, 5, 0, 0, 0, 0, 0, 0};
  // mul_test_big(mul11, mul22);
  // mul11.bits[2] = 0;
  // mul11.bits[0] = 125;
  // mul_test_big(mul11, mul22);
  // mul22.bits[0] = 100;
  // mul11.bits[0] = 1000;
  // mul_test_big(mul11, mul22);
  // mul11.bits[0] = 191567121;
  // mul_test_big(mul11, mul22);
  // mul11.bits[0] = 0;
  // mul22.bits[0] = 0;
  // mul11.bits[0] = 4294967295;
  // mul22.bits[0] = 4294967295;
  // mul_test_big(mul11, mul22);
  // mul11.bits[0] = 0;
  // mul22.bits[0] = 0;
  // mul11.bits[1] = 4294967295;
  // mul22.bits[1] = 4294967295;
  // mul_test_big(mul11, mul22);
  // mul11.bits[7] |= MINUS;
  // mul_test_big(mul11, mul22);
  // mul11.bits[7] = 0;
  // mul22.bits[7] |= MINUS;
  // mul_test_big(mul11, mul22);
  // mul11.bits[7] |= MINUS;
  // mul22.bits[7] |= MINUS;
  // mul_test_big(mul11, mul22);
  // printf("\n\n\ test \n\n");
  // mul11.bits[7] = (3 << 16) | MINUS;
  // mul22.bits[7] |= MINUS;
  // mul_test_big(mul11, mul22);
  // printf("%d", getExp(mul11.bits[7]));

  // mul11.bits[0] = 5234;
  // mul11.bits[1] = 0;
  // mul22.bits[0] = 2124;
  // mul22.bits[1] = 0;
  // mul11.bits[7] = (3 << 16) | MINUS;
  // mul22.bits[7] = (3 << 16) | MINUS;
  // mul_test_big(mul11, mul22);

  // printf("\n---------DIV-----------\n");
  // s21_decimal_big div11 = {1, 20, 5, 0, 0, 0, 0, 0};
  // s21_decimal_big div22 = {3, 0, 0, 0, 0, 0, 0, 0};
  // div_test_big(div11, div22);
  // div11.bits[0] = 1000;
  // div11.bits[1] = 0;
  // div22.bits[0] = 5;
  // div22.bits[1] = 0;
  // div_test_big(div11, div22);
  // div11.bits[0] = 0;
  // div11.bits[1] = 0;
  // div11.bits[2] = 345;
  // div22.bits[0] = 2;
  // div22.bits[1] = 0;
  // div_test_big(div11, div22);
  // div11.bits[0] = 0;
  // div11.bits[1] = 0;
  // div11.bits[2] = 600;
  // div22.bits[0] = 3;
  // div22.bits[1] = 0;
  // div_test_big(div11, div22);
  // div11.bits[0] = 0;
  // div11.bits[1] = 4294967295;
  // div11.bits[2] = 0;
  // div22.bits[0] = 0;
  // div22.bits[1] = 2;
  // div_test_big(div11, div22);
  // div11.bits[0] = 0;
  // div11.bits[1] = 0;
  // div11.bits[2] = 0;
  // div11.bits[3] = 3147483840;
  // div11.bits[4] = 0;
  // div22.bits[0] = 2;
  // div22.bits[1] = 0;
  // div_test_big(div11, div22);
  // div11.bits[0] = 123;
  // div11.bits[1] = 0;
  // div11.bits[2] = 0;
  // div22.bits[0] = 10;
  // div22.bits[1] = 0;
  // div_test_big(div11, div22);
  // div11.bits[7] |= MINUS;
  // div_test_big(div11, div22);
  // div22.bits[7] |= MINUS;
  // div_test_big(div11, div22);
  // div11.bits[0] = 17;
  // div11.bits[1] = 0;
  // div11.bits[2] = 0;
  // div11.bits[3] = 0;
  // div11.bits[4] = 0;
  // div22.bits[0] = 3;
  // div22.bits[1] = 0;
  // div22.bits[2] = 0;
  // div22.bits[3] = 0;

  // div11.bits[7] = 0;
  // div22.bits[7] = 0;
  // div_test_big(div11, div22);
  // div11.bits[0] = 42345;
  // div11.bits[1] = 42412;
  // div11.bits[2] = 1;
  // div11.bits[3] = 0;
  // div11.bits[4] = 0;
  // div22.bits[0] = 99123423;
  // div22.bits[1] = 0;
  // div22.bits[2] = 0;
  // div22.bits[3] = 0;
  // div_test_big(div11, div22);
  // printf("\n\n");
  // get_bits_big(div11);
  // printf("\n");
  // get_bits_big(div22);
  // printf("\n");
  return 0;
}

void int_to_decimal_test(s21_decimal res, int value) {
  s21_from_int_to_decimal(value, &res);
  printf("%d to decimal\nresult:\t", value);
  for (int i = 0; i <= 3; i++) printf("%u\t", res.bits[i]);
  printf("\n\n");
}

void float_to_decimal_test(s21_decimal res, float value) {
  s21_from_float_to_decimal(value, &res);
  printf("%f to decimal\nresult:\t", value);
  for (int i = 0; i <= 3; i++) printf("%u\t", res.bits[i]);
  printf("\n\n");
}

void decimal_to_int_test(s21_decimal res, int value) {
  s21_from_decimal_to_int(res, &value);
  printf("from decimal:\t");
  for (int i = 0; i <= 3; i++) printf("%u\t", res.bits[i]);
  printf("\nresult:\t%d\n\n", value);
}

void decimal_to_float_test(s21_decimal res, float value) {
  s21_from_decimal_to_float(res, &value);
  printf("from decimal:\t");
  for (int i = 0; i <= 3; i++) printf("%u\t", res.bits[i]);
  printf("\nresult:\t%f\n\n", value);
}

void is_less_test(s21_decimal value_1, s21_decimal value_2) {
  printf("value_1:\t");
  for (int i = 0; i <= 3; i++) printf("%u\t", value_1.bits[i]);
  printf("\nvalue_2:\t");
  for (int i = 0; i <= 3; i++) printf("%u\t", value_2.bits[i]);
  printf("\n");
  if (s21_is_less(value_1, value_2) == 1)
    printf("value_1 < value_2\n\n");
  else
    printf("value_1 > value_2\n\n");
}

void is_greater_test(s21_decimal value_1, s21_decimal value_2) {
  printf("value_1:\t");
  for (int i = 0; i <= 3; i++) printf("%u\t", value_1.bits[i]);
  printf("\nvalue_2:\t");
  for (int i = 0; i <= 3; i++) printf("%u\t", value_2.bits[i]);
  printf("\n");
  if (s21_is_greater(value_1, value_2) == 1)
    printf("value_1 > value_2\n\n");
  else
    printf("value_1 < value_2\n\n");
}

void is_eq_test(s21_decimal value_1, s21_decimal value_2) {
  printf("value_1:\t");
  for (int i = 0; i <= 3; i++) printf("%u\t", value_1.bits[i]);
  printf("\nvalue_2:\t");
  for (int i = 0; i <= 3; i++) printf("%u\t", value_2.bits[i]);
  printf("\n");
  if (s21_is_equal(value_1, value_2) == 1)
    printf("value_1 = value_2\n\n");
  else
    printf("value_1 != value_2\n\n");
}

void add_test(s21_decimal value_1, s21_decimal value_2) {
  s21_decimal res = {0};
  printf("value_1:\t");
  for (int i = 0; i <= 3; i++) printf("%u\t", value_1.bits[i]);
  printf("\nvalue_2:\t");
  for (int i = 0; i <= 3; i++) printf("%u\t", value_2.bits[i]);
  printf("\nresult:\t\t");
  s21_add(value_1, value_2, &res);
  for (int i = 0; i <= 3; i++) printf("%u\t", res.bits[i]);
  printf("\n\n");
}

void sub_test(s21_decimal value_1, s21_decimal value_2) {
  s21_decimal res = {0};
  printf("value_1:\t");
  for (int i = 0; i <= 3; i++) printf("%u\t", value_1.bits[i]);
  printf("\nvalue_2:\t");
  for (int i = 0; i <= 3; i++) printf("%u\t", value_2.bits[i]);
  printf("\nresult:\t\t");
  s21_sub(value_1, value_2, &res);
  for (int i = 0; i <= 3; i++) printf("%u\t", res.bits[i]);
  printf("\n\n");
}

void mul_test(s21_decimal value_1, s21_decimal value_2) {
  s21_decimal res = {0};
  printf("value_1:\t");
  for (int i = 0; i <= 3; i++) printf("%u\t", value_1.bits[i]);
  printf("\nvalue_2:\t");
  for (int i = 0; i <= 3; i++) printf("%u\t", value_2.bits[i]);
  printf("\nresult:\t\t");
  s21_mul(value_1, value_2, &res);
  for (int i = 0; i <= 3; i++) printf("%u\t", res.bits[i]);
  printf("\n\n");
}

void div_test(s21_decimal value_1, s21_decimal value_2) {
  s21_decimal res = {0};
  printf("value_1:\t");
  for (int i = 0; i <= 3; i++) printf("%u\t", value_1.bits[i]);
  printf("\nvalue_2:\t");
  for (int i = 0; i <= 3; i++) printf("%u\t", value_2.bits[i]);
  printf("\nresult:\t\t");
  s21_div(value_1, value_2, &res);
  for (int i = 0; i <= 3; i++) printf("%u\t", res.bits[i]);
  printf("\n\n");
}

void add_test_big(s21_decimal_big value_1, s21_decimal_big value_2) {
  s21_decimal_big res = {0};
  printf("value_1:\t");
  for (int i = 0; i <= 7; i++) printf("%u\t", value_1.bits[i]);
  printf("\nvalue_2:\t");
  for (int i = 0; i <= 7; i++) printf("%u\t", value_2.bits[i]);
  printf("\nresult:\t\t");
  s21_add_big(value_1, value_2, &res);
  for (int i = 0; i <= 7; i++) printf("%u\t", res.bits[i]);
  printf("\n\n");
}

void sub_test_big(s21_decimal_big value_1, s21_decimal_big value_2) {
  s21_decimal_big res = {0};
  printf("value_1:\t");
  for (int i = 0; i <= 7; i++) printf("%u\t", value_1.bits[i]);
  printf("\nvalue_2:\t");
  for (int i = 0; i <= 7; i++) printf("%u\t", value_2.bits[i]);
  printf("\nresult:\t\t");
  s21_sub_big(value_1, value_2, &res);
  for (int i = 0; i <= 7; i++) printf("%u\t", res.bits[i]);
  printf("t\n\n");
}

void mul_test_big(s21_decimal_big value_1, s21_decimal_big value_2) {
  s21_decimal_big res = {0};
  printf("value_1:\t");
  for (int i = 0; i <= 7; i++) printf("%u\t", value_1.bits[i]);
  printf("\nvalue_2:\t");
  for (int i = 0; i <= 7; i++) printf("%u\t", value_2.bits[i]);
  printf("\nresult:\t\t");
  s21_mul_big(value_1, value_2, &res);
  for (int i = 0; i <= 7; i++) printf("%u\t", res.bits[i]);
  printf("\n\n");
}

void div_test_big(s21_decimal_big value_1, s21_decimal_big value_2) {
  s21_decimal_big res = {0};
  printf("value_1:\t");
  for (int i = 0; i <= 7; i++) printf("%u\t", value_1.bits[i]);
  printf("\nvalue_2:\t");
  for (int i = 0; i <= 7; i++) printf("%u\t", value_2.bits[i]);
  printf("\nresult:\t\t");
  s21_div_big(value_1, value_2, &res);
  for (int i = 0; i <= 7; i++) printf("%u\t", res.bits[i]);
  printf("\n\n");
}