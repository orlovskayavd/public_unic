#include <stdio.h>
#include <string.h>
#define BUF_SIZE 100
#include <ctype.h>

size_t	number_alpha(char *str)
{
	size_t		number = 0;

	str--;
	while(*(++str))
		if (isalpha(*str))
			number++;
	return (number);
}

int		main(int argc, char **argv)
{
	FILE	*fwrite;
	FILE	*fread;
	char	str[BUF_SIZE];

	if (argc != 2)
	{
		printf ("ERROR!!!\nInvalid number of arguments\n");
		return (0);
	}
	if ((fread = fopen(argv[1], "r")) == NULL)
	{
		printf ("ERROR!!!\nFile to read did not open\n");;
		return (0);
	}
	if ((fwrite = fopen("10_out.txt", "w")) == NULL)
	{
		printf ("ERROR!!!\nFile to read did not open\n");;
		return (0);
	}
	while (fgets(str, BUF_SIZE, fread))
		fprintf(fwrite, "%zu\n", number_alpha(str));
	fclose(fwrite);
	fclose(fread);
}