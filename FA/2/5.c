#include <stdio.h>
#include <ctype.h>

int		main(int argc, char **argv)
{
	char *str = argv[1];
	char temp;
	if (argc != 2)
	{
		printf ("ERROR!!!\nInvalid number of arguments\n");
		return (0);
	}
	while (*(str + 1))
	{
		temp = *(str + 1);
		if (isdigit(temp) && isalpha(*str) || !isalnum(*str) && (isdigit(temp) || isalpha(temp)))
		{
			*(str + 1) = *str;
			*str = temp;
			str = argv[1];
			continue ;
		}
		str++;
	}
	printf("%s\n", argv[1]);
}