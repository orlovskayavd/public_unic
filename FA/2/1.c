#include <stdio.h>
#include <fcntl.h>
#include <ctype.h>
#define MAX_SIZE 128
 

int main(int argc, char **argv)
{
	FILE	*fread;
	int		array[MAX_SIZE];
	int 	size = 0;
	char	c;
	int		*ptr = array;
	int		number = 0;

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
	while ((c = fgetc(fread)) != -1)
	{
		if (isdigit(c))
		{
			number = number * 10 + c - '0';
			continue ;
		}
		if (c == ' ' || c == '\n' || c == '\t')
		{
			while ((c = fgetc(fread)) == ' ' || c == '\t' || c == '\n');
			if ((size + 1) % 2)
				*ptr++ = number;
			size++;
			number = 0;
			
			if (isdigit(c))
				number = c - '0';
			continue ;
		}
		printf("ERROR\n");
		return (0);
	}
	for (size_t i = 0; i < ptr - array; i++)
		printf("%d ", array[i]);
	return (0);
}