#include <stdio.h>

void	strrev(char *str)
{
	char *ptr_str = str;
	char temp;

	while (*str)
		str++;
	str--;
	while (str > ptr_str)
	{
		temp = *ptr_str;
		*ptr_str = *str;
		*str = temp;
		str--;
		ptr_str++;
	}
}

int	main()
{
	char str[20] = "12";
	printf("%s\n", str);
	strrev(str);
	printf("%s\n", str);
	return 0;
}