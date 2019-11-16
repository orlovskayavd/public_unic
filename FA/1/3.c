#include <stdio.h>
#include <ctype.h>
#include <string.h>

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
	if ((fwrite = fopen("3_out.txt", "w")) == NULL)
	{
		printf ("ERROR!!!\nFile to read did not open\n");;
		return (0);
	}
	while ((c = fgetc(fread)) != EOF)
	{
		if (!(isdigit(c)))
			fprintf(fwrite, "%c", c);
	}
	fclose(fwrite);
	fclose(fread);
	return (0);
}