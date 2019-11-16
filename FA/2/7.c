#include <stdarg.h>
#include <stdio.h>
#include <math.h>

double	geo_mean(int n, ...)
{
	double result = 1;

	va_list ptr;

	va_start(ptr, n);
	for (size_t i = 0; i < n; i++)
		result *= va_arg(ptr, double);
	va_end(ptr);
	return(pow(result, 1.0/n));
}

int main()
{
	printf("%lf\n", geo_mean(2, 9.0, 4.0));
	return 0;
}