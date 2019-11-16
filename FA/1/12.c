#include <stdio.h>
#include <string.h>
#define BUF_SIZE 100
#include <ctype.h>

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
	if ((fwrite = fopen("12_out.txt", "w")) == NULL)
	{
		printf ("ERROR!!!\nFile to read did not open\n");;
		return (0);
	}
	while (fgets(str, BUF_SIZE, fread))
	{
		number = 0;
		ptr = str - 1;
		while(*(++ptr))
			if (!isalnum(*ptr) && *ptr != ' ')
				number++;
		fprintf(fwrite, "%d\n", number);
	}
	fclose(fwrite);
	fclose(fread);
}