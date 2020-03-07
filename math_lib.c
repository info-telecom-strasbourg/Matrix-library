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
