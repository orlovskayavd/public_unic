#include <stdio.h>
#include <ctype.h>

int		main(int argc, char **argv)
{
	char *str = argv[1];
	
	if (argc != 2)
	{
		printf ("ERROR!!!\nInvalid number of arguments\n");
		return (0);
	}
	str--;
	while (*++str)
		if (!((argv[1] - str) % 2))
			*str = toupper(*str);
	printf("%s\n", argv[1]);
}