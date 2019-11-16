#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int		find(double eps, double a, double *array, int n)
{
	for (int i = 0; i < n; i++)
		if (fabs(array[i] - a) <= eps)
			return (1);
	return (0);
}

void	check_one(double eps, int base, double a)
{
	double *array;
	double	temp;
	int		size;
	int		n = 0;

	printf("%lf: ", a);
	size = 10;
	array = (double*)malloc(sizeof(double) * size);
	array[n++] = a;
	while(a > eps)
	{
		a *= base;
		a = modf(a, &temp);
		if (find(eps, a, array, n))
		{

			printf("NO\n");
			return ;
		}
		array[n] = a;
		n++;
	}
	printf ("YES\n");
}

void	check_all(int base, int n, ...)
{
	va_list		ptr;

	va_start(ptr, n);
	for (int i = 0; i < n; i++)
		check_one(0.000000001, base, va_arg(ptr, double));
	va_end(ptr);	
}

int		main()
{
	check_all(2, 4, 0.1123, 0.2, 0.3, 0.5);
}