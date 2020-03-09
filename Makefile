CFLAGS?=-Werror -Wextra -Wall -g

tests_matrix: tests_matrix.o math_lib.o
	gcc $(CFLAGS) -o tests_matrix $^

math_lib.o: math_lib.c math_lib.h
	gcc $(CFLAGS) -o math_lib.o -c math_lib.c

tests_matrix.o: tests_matrix.c
	gcc $(CFLAGS) -o tests_matrix.o -c tests_matrix.c

tests:
	sh test.sh


clean:
	rm -f *.o
	rm -f tests_matrix
