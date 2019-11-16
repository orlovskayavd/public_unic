#include <stdio.h>

size_t	ft_strlen(char *str)
{
	int count = 0;

	while (str[++count]);
	return(count);
}

int		main(int argc, char **argv)
{
	if (argc != 2)
	{
		printf ("ERROR!!!\nInvalid number of arguments\n");
		return (0);
	}
	printf("%zu\n", ft_strlen(argv[1]));
}