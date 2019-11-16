#include <stdio.h>

double	my_pow(double base, int power)
{
	if (power < 0)
	{
		power *= -1;
		base = 1 / base;
	}
	if (power == 0)
		return (1);
	return (base * my_pow(base, power - 1));
}

int		main()
{
	printf("%lf\n", my_pow(5.0, 3));
	return 0;
}