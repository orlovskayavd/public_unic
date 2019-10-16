#include <stdio.h>
#include <stdlib.h>

char	*transfer_other(int number, int r)
{
	int base = (1 << r) - 1;
	char *result;
	char *ptr;
	int size = 0;
	int temp = number;

	while (temp != 0)
	{
		size++;
		temp >>= r;
	}
	result = (char*)malloc(sizeof(char) * (size + 1));
	ptr = result + size;
	*ptr-- = 0;
	while (number != 0)
	{
		*ptr-- = (number & base) > 9 ? 'a' + (number & base) - 10 : '0' + (number & base);
		number >>= r;
	}
	return (result);
}

int		main()
{
	int number;
	int r;
	char *result;

	scanf("%d %d", &number, &r);
	if (r > 5 && r < 1)
	{
		printf("ERROR\n");
		return (-1);
	}
	result = transfer_other(number, r);
	printf("%s\n", result);
	free(result);
	return (0);
}