#include <stdio.h>
#include <string.h>
#define BUF_SIZE 100
#include <ctype.h>

int		base(char *str)
{
	int		max;
	int 	temp;

	if (isdigit(*str))
		max = *str - '0';
	else
		if (isalpha(tolower(*str)))
			max = tolower(*str) - 'a' + 10;
		else 
			return (-1);
	while (*(++str))
	{
		if (isdigit(*str))
			temp = *str - '0';
		else
			if (isalpha(tolower(*str)))
				temp = tolower(*str) - 'a' + 10;
			else 
				return (-1);
		if (temp > max)
			max = temp;
	}
	return (temp + 1);
}

int		convert(char *str, int base)
{
	int		result = 0;

	str--;
	while (*(++str))
		result = result * base + (isdigit(*str) ? *str - '0' : tolower(*str) - 'a' + 10);
	return (result);
}

int		main(int argc, char **argv)
{
	FILE	*fwrite;
	FILE	*fread;
	char	word[34];
	char	*ptr = word;
	int		base_int;
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
	if ((fwrite = fopen("17_out.txt", "w")) == NULL)
	{
		printf ("ERROR!!!\nFile to read did not open\n");;
		return (0);
	}
	while ((c = fgetc(fread)) != EOF)
	{
		if (!isspace(c))
		{
			*ptr = c;
			ptr++;
		}
		else
		{
			*ptr = 0;
			if ((base_int = base(word)) != -1)
				fprintf(fwrite, "%s base = %d decimal = %d\n", word, base_int, convert(word, base_int));
			ptr = word;
		}
	}
	fclose(fwrite);
	fclose(fread);
}