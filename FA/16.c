#include <stdio.h>
#include <string.h>
#define BUF_SIZE 100
#include <ctype.h>

int		main(int argc, char **argv)
{
	FILE	*fwrite;
	FILE	*fread;
	char	c;
	int		word;

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
	if ((fwrite = fopen("16_out.txt", "w")) == NULL)
	{
		printf ("ERROR!!!\nFile to read did not open\n");;
		return (0);
	}
	word = 1;
	while ((c = fgetc(fread)) != EOF)
	{
		if (isspace(c) || c == '\n')
		{
			fprintf(fwrite, "%c", c);
			word++;
			if (word == 6)
				word = 1;
			while ((c = fgetc(fread)) != EOF && isspace(c))
				fprintf(fwrite, "%c", c);
		}
		if (word == 2 && c != EOF)
			fprintf(fwrite, "%c", tolower(c));
		if (word == 5 && c != EOF)
			fprintf(fwrite, "%d", c);
		if (word != 5 && word != 2 && c != EOF)
			fprintf(fwrite, "%c", c);
	}
	fclose(fwrite);
	fclose(fread);
}