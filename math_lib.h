#ifndef MATH_LIB
#define MATH_LIB

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#define LENGTH_PRINT 10
#define CHK(op) do { \if (op == -1) raler(#op) ; } while (0)
#define CHK_ALLOC(op) do { if (op == NULL) fprintf(stderr, "alloc failure");}\
						while (0)
#define CHK_SNPRTF(op) do {int n; if ((n = op) >=  LENGTH_PRINT || n < 0)\
	 				fprintf(stderr, "snprintf failure");} while (0)

/**
 *@brief Calcul une puissance.
 *
 *@param a: the number.
 *@param exp: the exposant.
 *@result the result.
*/
long double mypow(long double a, int exp);

/**
 *@brief Create a matrix.
 *
 *@param nb_lines: the number of lines of the matrix.
 *@param nb_col: the number of columns of the matrix.
 *@result a matrix (two dimension table).
*/
long double** create_matrix(int nb_lines, int nb_col);

/**
 *@brief delete a matrix.
 *
 *@param nb_lines: the number of lines of the matrix.
*/
void delete_matrix(long double** mat, int nb_lines);

/**
 *
 *@param mat: a matrix.
 *@param nb_lines: the number of lines of the matrix.
 *@param nb_col: the number of columns of the matrix.
 *@param init: a table with the value of the matrix (line per line).
*/
void init_matrix(long double** mat, int nb_lines, int nb_col, long double* init);

/**
 *@brief Calculate a matrix addition.
 *
 *@param A: a matrix A (two dimension table).
 *@param lA: the number of lines of the matrix A.
 *@param cA: the number of columns of the matrix A.
 *@param B: a matrix B (two dimension table).
 *@param lB: the number of lines of the matrix B.
 *@param cB: the number of columns of the matrix B.
 *@param symb: the symbol of the opperation.
 *@result a matrix (two dimension table), the product of 2 matrix.
*/
long double** term_to_term_opp(long double**A, int lA, int cA,
			       long double**B, int lB, int cB, char symb);

/**
*@brief Calculate a matrix addition.
*
*@param A: a matrix A (two dimension table).
*@param lA: the number of lines of the matrix A.
*@param cA: the number of columns of the matrix A.
*@param symb: the symbol of the opperation.
*/
void all_terms_opp(long double**A, int lA, int cA,
			    float fact, char symb);

/**
 *@brief Calculate a matrix product.
 *
 *@param A: a matrix A (two dimension table).
 *@param lA: the number of lines of the matrix A.
 *@param cA: the number of columns of the matrix A.
 *@param A: a matrix B (two dimension table).
 *@param lB: the number of lines of the matrix B.
 *@param cB: the number of columns of the matrix B.
 *@result a matrix (two dimension table), the product of 2 matrix.
*/
long double** prod_matrix(long double**A, int lA, int cA,
			  long double**B, int lB, int cB);


/**
*@brief the longest number to print.
*
*@param mat: the matrix.
*@param nb_lines: the number of lines of the matrix.
*@param nb_col: the number of columns of the matrix.
*@result the maximum line length of the line.
*/
int max_line(long double** mat, int nb_lines, int nb_col);

/**
*@brief the longest number to print on the last column.
*
*@param mat: the matrix.
*@param nb_lines: the number of lines of the matrix.
*@param nb_col: the number of columns of the matrix.
*@result the maximum line length of the line.
*/
int max_last_line(long double** mat, int nb_lines, int nb_col);

/**
*@brief Print a matrix.
*
*@param mat: the matrix.
*@param nb_lines: the number of lines of the matrix.
*@param nb_col: the number of columns of the matrix.
*/
void print_matrix(long double** mat, int nb_lines, int nb_col);

/**
 *@brief Calculate a matrix product.
 *
 *@param A: a matrix A (two dimension table).
 *@param nb_lines: the number of lines of the matrix.
 *@param nb_col: the number of columns of the matrix.
 *@result the trace of the matrix.
*/
long double matrix_trace(long double** A, int nb_lines, int nb_col);

/**
 *@brief Calculate a matrix transpose.
 *
 *@param nb_lines: the number of lines of the matrix.
 *@param nb_col: the number of columns of the matrix.
 *@result a matrix transpose (two dimension table).
*/
long double** matrix_transpose(long double** mat, int nb_lines, int nb_col);

/**
 *@brief Calculate a matrix determinant.
 *
 *@param nb_lines: the number of lines of the matrix.
 *@param nb_col: the number of columns of the matrix.
 *@result the determinant of the matrix.
*/
long double matrix_det(long double** mat, int nb_lines, int nb_col);

/**
 *@brief Extract a matrix from an other.
 *
 *@param nb_lines: the number of lines of the matrix.
 *@param nb_col: the number of columns of the matrix.
 *@param l_extract: ligne to delete.
 *@param c_extract: column to extract
 *@result the extracted matrix.
*/
long double** matrix_extract(long double** mat, int nb_lines, int nb_col,
			     int l_extract, int c_extract);

/**
 *@brief Calculate a matrix invert.
 *
 *@param nb_lines: the number of lines of the matrix.
 *@param nb_col: the number of columns of the matrix.
 *@result the invert of the matrix.
*/
long double** co_matrix(long double** mat, int nb_lines, int nb_col);

/**
 *@brief Calculate a matrix invert.
 *
 *@param nb_lines: the number of lines of the matrix.
 *@param nb_col: the number of columns of the matrix.
 *@result the invert of the matrix.
*/
long double** matrix_invert(long double** mat, int nb_lines, int nb_col);

#endif
