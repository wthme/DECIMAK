#include "s21_test_decimal.h"

int main() {
  run_test();
  return 0;
}

void run_test() {
  Suite *s = NULL;
  SRunner *sr = NULL;

  s = s21_test_add();  //!!!!!!!!!!!!!!exp test
  sr = srunner_create(s);
  srunner_run_all(sr, CK_NORMAL);
  srunner_free(sr);

  s = s21_test_sub();  //!!!!!!!!!!!!!!exp test
  sr = srunner_create(s);
  srunner_run_all(sr, CK_NORMAL);
  srunner_free(sr);

  s = s21_test_mul();  //!!!!!!!!!!!!!!exp test
  sr = srunner_create(s);
  srunner_run_all(sr, CK_NORMAL);
  srunner_free(sr);

  s = s21_test_div();  //!!!!!!!!!!!!!!exp test
  sr = srunner_create(s);
  srunner_run_all(sr, CK_NORMAL);
  srunner_free(sr);

  s = s21_test_comparison();
  sr = srunner_create(s);
  srunner_run_all(sr, CK_NORMAL);
  srunner_free(sr);

  s = s21_test_convertors();
  sr = srunner_create(s);
  srunner_run_all(sr, CK_NORMAL);
  srunner_free(sr);

  s = s21_test_another_funct();
  sr = srunner_create(s);
  srunner_run_all(sr, CK_NORMAL);
  // srunner_free(sr);
  //Остальные добавлять по аналогии
}
