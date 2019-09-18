#include <stdio.h>
#include <string.h>
#define BUF_SIZE 100
#include <ctype.h>

int		main(int argc, char **argv)
{
	FILE	*fwrite;
	FILE	*fread1, *fread2;
	char	d, c;

	if (argc != 3)
	{
		printf ("ERROR!!!\nInvalid number of arguments\n");
		return (0);
	}
	if ((fread1 = fopen(argv[1], "r")) == NULL)
	{
		printf ("ERROR!!!\nFile to read did not open\n");;
		return (0);
	}
	if ((fread2 = fopen(argv[2], "r")) == NULL)
	{
		printf ("ERROR!!!\nFile to read did not open\n");;
		return (0);
	}
	if ((fwrite = fopen("15_out.txt", "w")) == NULL)
	{
		printf ("ERROR!!!\nFile to read did not open\n");;
		return (0);
	}
	while (d != EOF || c != EOF)
	{
		if (isprint(c))
			fprintf(fwrite, "%c", c);
		while (((c = fgetc(fread1)) != EOF) && !isspace(c))
			fprintf(fwrite, "%c", c);
		while (((c = fgetc(fread1)) != EOF) && isspace(c));
		if (d != EOF)	
			fprintf(fwrite, " ");
		if (isprint(d))
			fprintf(fwrite, "%c", d);
		while (((d = fgetc(fread2)) != EOF) && !isspace(d))
			fprintf(fwrite, "%c", d);
		while (((d = fgetc(fread2)) != EOF) && isspace(d));
		if (c != EOF)
			fprintf(fwrite, " ");
	}
	fclose(fwrite);
	fclose(fread1);
	fclose(fread2);
}