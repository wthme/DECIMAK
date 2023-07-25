GFLAGS = gcc -Wall -Werror -Wextra -std=c11
OS = -lcheck
UNAME = $(shell uname -s)
GCOV_FLAGS = -L. --coverage 

ifeq ($(UNAME), Linux)
	OS = -lcheck -lm -lpthread -lrt -lsubunit
endif

TEST = src_test
REPORT = report
GCOV = gcov


SRC_DECIMAL = *.c
OBJ_DECIMAL = *.o
LIB_DECIMAL = s21_decimal.a

S21_TEST = $(TEST)/s21_test
SRC_TEST = $(TEST)/*.c

all: $(LIB_DECIMAL)
	$(GFLAGS)  $(SRC_TEST) -o $(S21_TEST) $(LIB_DECIMAL) $(OS)

test : $(LIB_DECIMAL)
	$(GFLAGS) $(SRC_TEST) -o $(S21_TEST) $(LIB_DECIMAL) $(OS)
	./$(S21_TEST)

s21_decimal.a :
	$(GFLAGS) -c $(SRC_DECIMAL)
	ar rcs $(LIB_DECIMAL) $(OBJ_DECIMAL)

clean:
	rm -rf  *.o *.a
	rm -rf *.gcda *.gcno *.info

c:
	clang-format --style=Google -i *.c *.h

gcov_report: test
	rm -rf *.g*
	${CC} s21_*.c src_test/run_test.c src_test/s21_test_*.c src_test/helpful_test_function.c s21_decimal.a ${OS} ${GCOV_FLAGS} -g
	./a.out
	lcov -t a.out -o test.info -c -d .
	genhtml -o report test.info
	open ./report/index.html
	rm -rf *.gcda *.gcno *.info
