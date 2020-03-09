CFLAGS?=-Werror -Wextra -Wall -g -fprofile-arcs -ftest-coverage

tests_matrix: tests_matrix.o math_lib.o
	gcc $(CFLAGS) -o tests_matrix $^

math_lib.o: math_lib.c math_lib.h
	gcc $(CFLAGS) -o math_lib.o -c math_lib.c

tests_matrix.o: tests_matrix.c
	gcc $(CFLAGS) -o tests_matrix.o -c tests_matrix.c

tests:
	@echo "\033[0;34m==== Compilation ====\033[0m"
	@make clean >/dev/null
	@make >/dev/null
	@echo "\033[0;32mOK\033[0m"

	@echo "\033[0;34m==== Execution ====\033[0m"
	@./tests_matrix
	@echo "\n\033[0;32mOK\033[0m"

	@echo "\033[0;34m==== Valgrind ====\033[0m"
	@valgrind --error-exitcode=43 --leak-check=full -q ./tests_matrix
	@echo "\n\033[0;32mOK\033[0m"

	@echo "\033[0;34m==== Coverage Generation ====\033[0m"
	@lcov -d . -c -o rapport.info >/dev/null
	@genhtml -o rapport -t "Couverture" rapport.info >/dev/null
	@echo "\033[0;32mOK\033[0m"


clean:
	rm -f *.o
	rm -f tests_matrix
