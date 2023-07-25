#include "s21_test_decimal.h"

s21_decimal convert_ll_to_decimal(long long val) {
  s21_decimal res = {0};
  if (val < 0) {
    setSignInt(1, &res);
    val = -val;
  }

  for (__uint64_t i = 0; val; i++, val /= 2) {
    if (val % 2) {
      res.bits[i / 32] |= (1U << i);
    }
  }
  return res;
}

long long random_ll() {
  long long val = 0;
  for (__uint64_t i = 0; i < 64; i++) {
    if (rand() % 2) {
      val |= (1U << i);
    }
  }
  return val;
}

float random_float(float min, float max) {
  float result = 0;
  float random = (float)rand() / (float)RAND_MAX;
  float range = max - min;
  result = random * range + min;
  return result;
}