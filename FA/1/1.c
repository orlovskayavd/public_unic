#include <stdlib.h>
#include <stdio.h>

int	main()
{
	int a;

	scanf("%d", &a);
	for (size_t i = 1; i * a < 100; i++)
		printf ("%ld ", a * i);
	printf("\n");
	return (0);
}