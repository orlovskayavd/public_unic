#include <stdio.h>

int		main()
{
	int		a, c;

	scanf("%d %d", &a, &c);
	if (!c)
	{
		printf("ERROR\n");
		return (0);
	}
	printf("%s", a % c ? "NO\n" : "YES\n");
	return (0);
}