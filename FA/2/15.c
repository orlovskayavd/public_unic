#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>


int		change(int x, int n, ...)
{
	va_list	ptr;
	int		result = 0;
	
	n++;
	va_start(ptr, n);
	for (int i = 0; i < n; i++)
		result = result * x + va_arg(ptr, int);
	return (result);
}

int		main()
{
	printf("%d\n", change(2, 3, 0, 3, 2, 1));
}