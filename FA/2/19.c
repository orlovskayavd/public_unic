#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#define SIZE_ARRAY 10

int		main(void)
{
	int *array_2;
	int array[SIZE_ARRAY];
	int number_indetical = 0;
	int flag;
	int *ptr;
	
	srand(time(NULL));
	printf("array_1: ");
	for (int i = 0; i < SIZE_ARRAY; i++)
	{	
		array[i] = rand() % 20 - 10;
		for (int j = 0; j < i; j++)
		{
			if (array[i] == array[j])
			{
				number_indetical++;
				break ;
			}
		}
		printf("%d ", array[i]);
	}
	printf("\n");
	array_2 = (int*)malloc(sizeof(int) * (SIZE_ARRAY - number_indetical));
	ptr = array_2;
	for (int i = 0; i < SIZE_ARRAY; i++)
	{
		flag = 0;
		for (int j = 0; j < i; j++)
			if (array[j] == array[i])
			{
				flag = 1;
				break ;
			}
		if (!flag)
			*ptr++ = array[i];
	}
	for (int i = 0; i < SIZE_ARRAY - number_indetical; i++)
		printf("%d ", array_2[i]);
	printf("\n");
}