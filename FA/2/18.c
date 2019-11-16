#include <stdio.h>
#define SIZE_ARRAY 3

void	print_matrix(int matrix[SIZE_ARRAY][SIZE_ARRAY])
{
	for (int i = 0; i < SIZE_ARRAY; i++)
	{
		for (int j = 0; j < SIZE_ARRAY; j++)
			printf("%d ", matrix[i][j]);
		printf("\n");
	}
}

void my_swap(int matrix[SIZE_ARRAY][SIZE_ARRAY], int i1, int i2)
{
	int temp;

	for (int j = 0; j < SIZE_ARRAY; j++)
	{
		temp = matrix[i1][j];
		matrix[i1][j] = matrix[i2][j];
		matrix[i2][j] = temp;	
	}
	
}
int	triangle_matrix(int matrix[SIZE_ARRAY][SIZE_ARRAY])
{
	int mnoj;

	mnoj = 1;
	for (int diag = 0; diag < SIZE_ARRAY - 1; diag++)
	{
		if (!matrix[diag][diag])
			for (int i = diag; i < SIZE_ARRAY - 1; i++)
				if (matrix[i][i])
				{
					my_swap(matrix, i, diag);
					mnoj *= -1;
				}
		for (int i = diag + 1; i < SIZE_ARRAY; i++)
		{
			if (!matrix[i][diag])
				continue ;
			for (int j = diag + 1; j < SIZE_ARRAY; j++)
				matrix[i][j] = matrix[diag][diag] * matrix[i][j] - matrix[i][diag] * matrix[diag][j];
			mnoj *= matrix[diag][diag];
			matrix[i][diag] = 0;
		}		  		
	}
	return (mnoj);
}

int		det(int matrix[SIZE_ARRAY][SIZE_ARRAY])
{
	int det;
	int temp;

	temp = triangle_matrix(matrix);
	det = 1;
	for (int i = 0; i < SIZE_ARRAY; i++)	
		det *= matrix[i][i];
	return (det / temp);
}


int		main(void)
{
	int matrix[SIZE_ARRAY][SIZE_ARRAY] = {{5, 3, 1}, {7, 8, 96}, {1, 5, 8}};
	printf("%d\n", det(matrix));
	print_matrix(matrix);
}