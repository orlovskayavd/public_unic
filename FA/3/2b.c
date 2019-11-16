#include <stdio.h>

int		check_number(int number, int l)
{
	int check = l;

	while(number)
	{
		if (number & 1)
			check--;
		else
		{
			if (!check)
				return (1);
			check = l;
		}
		number >>= 1;
	}
	return (check == 0);
}

int main()
{
	int k;
	int l;
	int number_max;
	int i = -1;
	int result = 0;

	scanf("%d %d", &k, &l);
	if (l > k)
	{
		printf("ERROR\n");
		return (0);
	}
	number_max = 1 << k;
	
	while (++i < number_max)
		result += check_number(i, l);
	printf("result = %d\n", result);
	return (0);
}