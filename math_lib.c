#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "math_lib.h"

long double
mypow(long double a, int exp)
{
	if (exp == 0)
		return 1;

	long double res = 1;
	for (int i = 0; i < exp; i++)
		res*=a;
	return res;
}

long double**
create_matrix(int nb_lines, int nb_col)
{
	long double** mat = malloc(nb_lines*sizeof(long double*));

	if (mat == NULL)
		return NULL;

	for (int i = 0; i < nb_lines; i++)
	{
		mat[i] = malloc(nb_col*sizeof(long double));
		if (mat[i] == NULL)
		{
			for (int j=0; j < i ; j++)
				free(mat[j]);
			free(mat);
			return NULL;
		}

		for (int j = 0; j < nb_col; j++)
			mat[i][j] = 0;
	}
	return mat;
}

void
delete_matrix(long double** mat, int nb_lines)
{
	for (int i = 0; i < nb_lines; i++)
		free(mat[i]);

	free(mat);
}

void
init_matrix(long double** mat, int nb_lines, int nb_col, long double* init)
{
	int iter = 0;
	for (int i = 0; i < nb_lines; i++)
		for (int j = 0; j < nb_col; j++,iter++)
			mat[i][j] = init[iter];
}

long double**
term_to_term_opp(long double**A, int lA, int cA,
			       long double**B, int lB, int cB, char symb)
{
	if (cA != lB || lA != lB)
	{
		fprintf(stderr, "dimension problem in term_to_term_opp()\n");
		return NULL;
	}

	long double** C = create_matrix(lA, cA);
	if (C == NULL)
		return NULL;

	switch(symb)
	{
		case '+':
			for (int i=0; i <lA; i++)
				for (int j=0; j< cB; j++)
					C[i][j] = A[i][j] + B[i][j];
			break;
		case '-':
			for (int i=0; i <lA; i++)
				for (int j=0; j< cB; j++)
					C[i][j] = A[i][j] - B[i][j];
			break;
		case '*':
			for (int i=0; i <lA; i++)
				for (int j=0; j< cB; j++)
					C[i][j] = A[i][j] * B[i][j];
			break;
		case '/':
			for (int i=0; i <lA; i++)
				for (int j=0; j< cB; j++)
					if (B[i][j] != 0)
						C[i][j] = A[i][j] / B[i][j];
					else
						fprintf(stderr, "/0: \
							term_to_term_opp\n");
			break;
		default:
			fprintf(stderr, "term_to_term_opp: not an\
			 	opperation\n");
	}

	return C;
}

void
all_terms_opp(long double**A, int lA, int cA,
			    float fact, char symb)
{
	switch(symb)
	{
		case '+':
			for (int i=0; i <lA; i++)
				for (int j=0; j< cA; j++)
					A[i][j] += fact;
			break;
		case '-':
			for (int i=0; i <lA; i++)
				for (int j=0; j< cA; j++)
					A[i][j] -= fact;
			break;
		case '*':
			for (int i=0; i <lA; i++)
				for (int j=0; j< cA; j++)
					A[i][j] *= fact;
			break;
		case '/':
			for (int i=0; i <lA; i++)
				for (int j=0; j< cA; j++)
					if (fact != 0)
						A[i][j] /= fact;
					else
						fprintf(stderr, "/0: \
							term_to_term_opp\n");
			break;
		default:
			fprintf(stderr, "term_to_term_opp: not an \
					opperation\n");
	}
}

long double**
matrix_prod(long double**A, int lA, int cA,
			  long double**B, int lB, int cB)
{
	if (cA != lB)
	{
		fprintf(stderr, "dimension error in matrix_prod()\n");
		return NULL;
	}

	long double** C = create_matrix(lA, cB);

	if (C == NULL)
		return NULL;

	long double cij = 0;
	for (int i=0; i <lA; i++)
	{
		for (int j=0; j< cB; j++)
		{
			cij = 0;
			for (int k = 0; k < cA; k++)
				cij += A[i][k] * B[k][j];
			C[i][j] = cij;
		}
	}
	return C;
}

int
max_line(long double** mat, int nb_lines, int nb_col)
{
	char buf[10];
	int length = 0;
	int max_length = 0;
	for (int i=0; i < nb_lines; i++)
	{
		for (int j=0; j < nb_col; j++)
		{
			buf[0] = '\0';
			CHK_SNPRTF(snprintf(buf,LENGTH_PRINT, "%.2Lf",
					    mat[i][j]));
			length = strlen(buf);

			if (length > max_length)
				max_length = length;
		}

	}
	return max_length;
}

int
max_last_line(long double** mat, int nb_lines, int nb_col)
{
	char buf[10];
	int length = 0;
	int max_length = 0;
	for (int i=0; i < nb_lines; i++)
	{
		buf[0] = '\0';
		CHK_SNPRTF(snprintf(buf,LENGTH_PRINT, "%.2Lf",
			     mat[i][nb_col-1]));
		length = strlen(buf);

		if (length > max_length)
			max_length = length;

	}
	return max_length;
}

void
print_matrix(long double** mat, int nb_lines, int nb_col)
{
	int line_length = max_line(mat, nb_lines, nb_col);
	int max_last_ln = max_last_line(mat, nb_lines, nb_col);
	char buf[10];
	printf(" --");

	for (int i = 2; i < (nb_col-1)*(line_length + 2) + max_last_ln +1; i++)
		printf(" ");

	printf("--\n");
	for (int i=0; i < nb_lines; i++)
	{
		printf("| ");
		for (int j=0; j < nb_col-1; j++)
		{
			buf[0] = '\0';
			CHK_SNPRTF(snprintf(buf, LENGTH_PRINT,"%.2Lf",
					    mat[i][j]));
			printf("%s", buf);

			for (int j = strlen(buf); j < line_length +2; j++)
				printf(" ");
		}
		buf[0] = '\0';
		CHK_SNPRTF(snprintf(buf, LENGTH_PRINT,"%.2Lf",
				      mat[i][nb_col-1]));
		printf("%s", buf);

		for (int j = strlen(buf); j < max_last_ln +2; j++)
			printf(" ");
		printf("|\n");
	}
	printf(" --");

	for (int i = 2; i < (nb_col-1)*(line_length + 2) + max_last_ln +1; i++)
		printf(" ");

	printf("--\n");
}

long double
matrix_trace(long double** A, int nb_lines, int nb_col)
{
	if (nb_lines != nb_col)
		fprintf(stderr, "trace used on a not a square matrix\n");

	long double trace = 0;
	for (int i = 0; i < nb_lines; i++)
		trace += A[i][i];

	return trace;
}

long double**
matrix_transpose(long double** mat, int nb_lines, int nb_col)
{
	long double** mat_transp = create_matrix(nb_col, nb_lines);

	if (mat_transp == NULL)
		return NULL;

	for (int i = 0; i < nb_lines; i++)
		for (int j = 0; j < nb_col; j++)
			mat_transp[j][i] = mat[i][j];

	return mat_transp;
}

long double
matrix_det(long double** mat, int nb_lines, int nb_col)
{

	if (nb_lines != nb_col)
		fprintf(stderr, "trace used on a not a square matrix\n");

	if (nb_col == 2)
		return (mat[0][0]*mat[1][1] - mat[1][0]* (mat[0][1]));

	if (nb_lines == 1)
		return mat[0][0];

	int det = 0;
	for (int i = 0; i < nb_col; i++)
	{
		long double** under_mat = create_matrix(nb_lines-1, nb_col-1);

		if (under_mat == NULL)
		{
			fprintf(stderr, "allocation failed in matrix_det()\n");
			return 0;
		}

		for (int k = 0; k < nb_lines-1; k++)
		{
			for (int l = 0; l < i; l++)
				under_mat[k][l] = mat[k+1][l];
			for (int l = i; l < nb_col-1; l++)
				under_mat[k][l] = mat[k+1][l+1];
		}

		det += mypow(-1,i)*mat[0][i] * matrix_det(under_mat, nb_lines-1,
			 			          nb_col-1);

		delete_matrix(under_mat, nb_lines-1);
	}
	return det;
}

long double**
matrix_extract(long double** mat, int nb_lines, int nb_col,
			     int l_extract, int c_extract)
{

	long double** extract_mat = create_matrix(nb_lines-1, nb_col-1);

	if (extract_mat == NULL)
		return NULL;

	for (int i = 0; i < l_extract; i++)
	{
		for (int j = 0; j < c_extract; j++)
			extract_mat[i][j] = mat[i][j];

		for (int j = c_extract; j < nb_col-1; j++)
			extract_mat[i][j] = mat[i][j+1];
	}

	for (int i = l_extract; i < nb_lines-1; i++)
	{
		for (int j = 0; j < c_extract; j++)
			extract_mat[i][j] = mat[i+1][j];

		for (int j = c_extract; j < nb_col-1; j++)
			extract_mat[i][j] = mat[i+1][j+1];
	}
	return extract_mat;
}
