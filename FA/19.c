#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#define SIZE_ARRAY 10

typedef struct	t_near
{
	int		index;
	int		number;
}				s_near;

int		main(int argc, char **argv)
{
	int 		array_1[SIZE_ARRAY];
	int 		array_2[SIZE_ARRAY];
	int 		array_3[SIZE_ARRAY];
	s_near			near;

	srand(time(NULL));
	printf ("array_1: ");
	for (int i = 0; i < SIZE_ARRAY; i++)
	{
		array_1[i] = rand() % SIZE_ARRAY;
		printf("%d ", array_1[i]);
	}
	printf ("\narray_2: ");
	for (int i = 0; i < SIZE_ARRAY; i++)
	{
		array_2[i] = rand() % SIZE_ARRAY;
		printf("%d ", array_2[i]);
	}
	for (int i = 0; i < SIZE_ARRAY; i++)
	{
		near.index = 0;
		near.number = abs(array_1[i] - array_2[0]);
		for (int j = 0; j < SIZE_ARRAY; j++)
		{
			if (near.number > abs((array_1[i] - array_2[j])))
			{
				near.index = j;
				near.number = abs((array_1[i] - array_2[j]));
			}
		}
		array_3[i] = array_1[i] + array_2[near.index];
	}
	printf("\narray_3: ");
	for (int i = 0; i < SIZE_ARRAY; i++)
		printf("%d ", array_3[i]);
}