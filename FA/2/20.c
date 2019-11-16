#include <stdlib.h>
#include <time.h>
#include <stdio.h>

typedef struct	s_matrix
{
	int n;
	int m;
	int **matrix;
}				t_matrix;

void	print_matrix(t_matrix matrix)
{
	for (int i = 0; i < matrix.n; i++)
	{
		for (int j = 0; j < matrix.m; j++)
			printf("%3d ", matrix.matrix[i][j]);
		printf("\n");
	}
}

void	initialization(t_matrix *matrix)
{
	matrix->matrix = (int**)malloc(sizeof(int*) * matrix->n);
	for (int i = 0; i < matrix->n; i++)
	{
		matrix->matrix[i] = (int*)malloc(sizeof(int) * matrix->m);
		for (int j = 0; j < matrix->m; j++)
			matrix->matrix[i][j] = rand() % 20 - 10;
	}
}
int		one_cell(int **matrix_1, int **matrix_2, int i, int j, int n)
{
	int result = 0;
	for (int k = 0; k < n; k++)
		result += matrix_1[i][k] * matrix_2[k][j];
	return (result);
}
t_matrix		mult(t_matrix matrix_1, t_matrix matrix_2)
{
	t_matrix matrix_result;

	if (matrix_1.m != matrix_2.n)
	{
		printf("ERROR\n");
		exit(1);
	}
	matrix_result.n = matrix_1.n;
	matrix_result.m = matrix_2.m;
	matrix_result.matrix = (int**)malloc(sizeof(int*) * matrix_result.n);
	for (int i = 0; i < matrix_result.n; i++)
	{
		matrix_result.matrix[i] = (int*)malloc(sizeof(int) * matrix_result.m);
		for (int j = 0; j < matrix_result.m; j++)
			matrix_result.matrix[i][j] = one_cell(matrix_1.matrix, matrix_2.matrix, i, j, matrix_1.m); 
	}
	return (matrix_result);
}

int		main()
{
	t_matrix matrix_1, matrix_2;

	srand(time(NULL));
	matrix_1.n = 3;
	matrix_1.m = 3;
	initialization(&matrix_1);
	print_matrix(matrix_1);
	matrix_2.n = 3;
	matrix_2.m = 3;
	printf("\n");
	initialization(&matrix_2);
	print_matrix(matrix_2);
	printf("\n");
	print_matrix(mult(matrix_1, matrix_2));	
}