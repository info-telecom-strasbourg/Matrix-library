#ifndef MATH_LIB
#define MATH_LIB

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#define LENGTH_PRINT 10
#define CHK(op) do { \if (op == -1) raler(#op) ; } while (0)
#define CHK_ALLOC(op) do { if (op == NULL) usage("alloc failure");}while (0)
#define CHK_SNPRTF(op) do {int n; if ((n = op) >=  LENGTH_PRINT || n < 0)\
	 				usage("snprintf failure");} while (0)

/**
 *@brief Create a matrix.
 *
 *@param nb_lines: the number of lines of the matrix.
 *@param nb_col: the number of columns of the matrix.
 *@result a matrix (two dimension table).
*/
long double** create_matrix(int nb_lines, int nb_col);
