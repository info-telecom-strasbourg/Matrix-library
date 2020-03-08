#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "math_lib.h"

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
