#include <stdio.h>
#include <math.h>

double	function(double x)
{
	return (x * x * x - 3 * x + 1);
}

double dexot(double a, double b, double eps)
{
	double c;

	c = (a + b) / 2;
	while (b - a > eps)
	{
		c = (a + b) / 2;
		if (function(c) * function(a) < 0)
			b = c;
		else
			a = c;
	}
	return (c);
}

int main()
{
	printf("%lf\n", dexot(0, 1.0, 0.001));
}