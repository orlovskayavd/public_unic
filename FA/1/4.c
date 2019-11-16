#include <math.h>
#include <stdio.h>

int		main()
{
	double a, b, c;

	scanf("%lf %lf %lf", &a, &b, &c);
	if (pow(b, 2) - 4 * a * c >= 0)
	{
		printf("x1 = %lf\n", (-b + sqrt(pow(b, 2.0) - 4 * a * c)) / (2 * a));
		printf("x2 = %lf\n", (-b - sqrt(pow(b, 2.0) - 4 * a * c)) / (2 * a));
	}
	else
		printf("ERROR\n");
	return (0);
}