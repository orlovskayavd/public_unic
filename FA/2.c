#include <stdio.h>
#include <stdlib.h>

int		main()
{
	int a;
	while (1)
	{
		scanf("%d", &a);
		if (a == 0)
			return (0);
		if (a < 0)
		{
			printf("ERROR");
			continue ;
		}
		if (a == 2 || a == 1)
		{
			if (a == 2)
				printf("YES\n");
			else
				printf("NO\n");
			continue ;
		}
		for (size_t i = 2; i * i < a; i++)
		{
			if (!(a % i))
			{
				printf("NO\n");
				a = 0;
				break ;
			}
		}
		if (a != 0)
			printf("YES\n");
	}
}