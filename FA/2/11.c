#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define SIZE_ARRAY 10

void my_swap(int *a, int *b)
{
	int temp = *a;

	*a = *b;
	*b = temp;
}

typedef struct	t_min_max
{
	int		index;
	int		number;
}				s_min_max;

int		main(int argc, char **argv)
{
	int 		array[SIZE_ARRAY];
	s_min_max	min, max;

	srand(time(NULL));
	for (int i = 0; i < SIZE_ARRAY; i++)
	{
		array[i] = rand() % SIZE_ARRAY - 20;
		printf("%d ", array[i]);
	}
	printf("\n");
	min.index = 0;
	min.number = array[0];
	max.index = 0;
	max.number = array[0];
	for (int i = 0; i < SIZE_ARRAY; i++)
	{
		if (min.number > array[i])
		{
			min.number = array[i];
			min.index = i;
		}
		if (max.number < array[i])
		{
			max.index = i;
			max.number = array[i];
		}
	}
	my_swap(array + max.index, array + min.index);
	for (int i = 0; i < SIZE_ARRAY; i++)
		printf("%d ", array[i]);
	printf("\n");
}