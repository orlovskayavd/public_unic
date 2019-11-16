#include <stdio.h>
#include <string.h>
#define BUF_SIZE 100
#include <ctype.h>

void	print_str(char *str, FILE *fwrite)
{
	char *ptr;

	ptr = str;
	while (*str != '\t' && *str != ' ' )
		str++;
	*str = 0;
	while (*++str != '\n')
		fprintf(fwrite, "%c", *str);
	fprintf(fwrite, " %s\n", ptr);
}

int		main(int argc, char **argv)
{
	FILE	*fwrite;
	FILE	*fread;
	char	str[BUF_SIZE];
	char	*ptr = NULL;
	int		number;

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
	if ((fwrite = fopen("13_out.txt", "w")) == NULL)
	{
		printf ("ERROR!!!\nFile to read did not open\n");;
		return (0);
	}
	while (fgets(str, BUF_SIZE, fread))
		print_str(str, fwrite);
	fclose(fwrite);
	fclose(fread);
}