#include <stdio.h>
#include "tps_unit_test_2.h"
#include "math_lib.h"

#define COLOR_OFF "\033[0m"
#define GREEN "\033[0;32m"
#define BLUE "\033[0;34m"
#define CYAN "\033[0;36m"

int __remaining_alloc;

void test_create_matrix(void)
{
	__remaining_alloc = -1;
	long double** test = create_matrix(3, 3);

	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			tps_assert(test[i][j] == 0);

	delete_matrix(test, 3);
}

void test_alloc_fail(void)
{
	__remaining_alloc = 0;
	long double** test = create_matrix(3, 3);
	tps_assert(test == NULL);
}

void test_initialisation(void)
{
	__remaining_alloc = -1;

	long double** test = create_matrix(5,5);

	long double init_test[25] = {2,3,-1,3,1,
		          3,1,-4,3,-1,
		  	  1,-2,3,-4,2,
		  	  1,2,-3,2,-2,
		  	  2,0,0,4,-5};

	init_matrix(test, 5, 5, init_test);

	for (int i = 0, iter = 0; i < 5; i++)
		for (int j = 0; j < 5; j++, iter++)
			tps_assert(test[i][j] == init_test[iter]);

	delete_matrix(test, 5);
}

int main(void) {
	printf(CYAN "\n==== Fonctions de bases ====\n" COLOR_OFF);
	TEST(test_create_matrix);
	TEST(test_alloc_fail);
	TEST(test_initialisation);
	return 0;
}
