#include <stdio.h>
#include <string.h>
#define BUF_SIZE 100
#include <ctype.h>

int		main(int argc, char **argv)
{
	FILE	*fwrite;
	FILE	*fread;
	char	c;

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
	if ((fwrite = fopen("14_out.txt", "w")) == NULL)
	{
		printf ("ERROR!!!\nFile to read did not open\n");;
		return (0);
	}
	while ((c = fgetc(fread)) != EOF)
	{
		if (!isdigit(c) && c != '\n')
			fprintf(fwrite, "%d", c);
		else
			fprintf(fwrite, "%c", c);
	}
	fclose(fwrite);
	fclose(fread);
}