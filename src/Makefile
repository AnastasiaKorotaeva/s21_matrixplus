CC = gcc -std=c++17 -Wall -Werror -Wextra -pedantic -lstdc++
LIBS = -lgtest -pthread
GCOV = --coverage

all: clean s21_matrix_oop.a test

s21_matrix_oop.a:
	$(CC) -c s21_matrix_oop.cc -o s21_matrix_oop.o
	ar rcs s21_matrix_oop.a s21_matrix_oop.o

test: clean
	$(CC) s21_matrix_oop.cc test.cc -o matrix_test $(LIBS)
	./matrix_test

gcov_report: clean
	$(CC) $(GCOV) -c s21_matrix_oop.cc 
	$(CC) -c test.cc $(LIBS)
	$(CC) $(GCOV) -o matrix_test test.o s21_matrix_oop.o $(LIBS)
	./matrix_test
	lcov -t "test" -o s21_matrix_oop.info -c -d .
	genhtml -o report s21_matrix_oop.info
	open ./report/index.html
	make clean_test

check_style:
	clang-format -style=Google -n *.cc *.h
	
clean_test:
	rm -rf *.gcda *.gcno *.info matrix_test 
	
clean: clean_test
	rm -rf ./*.o ./*.a report 