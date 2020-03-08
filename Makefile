CFLAGS?=-Werror -Wextra -Wall -g

tests_matrix: test_matrix.o math_lib.o
	gcc $(CFLAGS) -o tests $^

math_lib.o: math_lib.c math_lib.h
	gcc $(CFLAGS) -o math_lib.o -c math_lib.c

test_matrix.o: test_matrix.c
	gcc $(CFLAGS) -o test_matrix.o -c test_matrix.c

tests:
	make
	valgrind --leak-check=full -q ./tests


clean:
	rm -f *.o
	rm -f tests
