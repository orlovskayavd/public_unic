#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define BUFF_SIZE 1000
typedef struct	s_message
{
	int		id;
	char	*str;
	int		byte;
}				Message;


int main()
{
	FILE *f1;
	Message *array;
	Message		mess;
	int id = 0;
	char c;
	char *ptr;
	char *str;
	int size = 0;


	f1 = fopen("4.txt", "w");
	while (1)
	{
		printf("Write message:\n");
		size = 0;
		str = (char*)malloc(sizeof(char) * (size + 1));
		while ((c = getchar()) != '\n')
		{
			size++;
			str = (char*)realloc(str, sizeof(str) * (size + 1));
			str[size - 1] = c;
		}
		str[size] = 0;
		mess.str = str;
		if (!(strcmp(mess.str, "stop")))
			break ;
		mess.id = id++;
		mess.byte = strlen(mess.str);	
		fprintf(f1, "%d %d %s\n", mess.id, mess.byte, str);
	}
	printf("\n");
	fclose(f1);
	f1 = fopen("4.txt", "r");
	array = (Message*)malloc(sizeof(Message) * id);
	for (int i = 0; i < id; i++)
	{
		array[i].id = 0;
		while (isdigit((c = fgetc(f1))))
			array[i].id = array[i].id * 10 + c - '0';
		array[i].byte = 0;
		while (isdigit((c = fgetc(f1))))
			array[i].byte = array[i].byte * 10 + c - '0';
		array[i].str = (char*)malloc(sizeof(char) * 100);
		ptr = array[i].str;
		while ((c = fgetc(f1)) != '\n')
			*ptr++ = c;
		*ptr = 0;
	}
	for (int i = 0; i < id; i++)
		printf("id = %d\nbyte = %d\nmessage = %s\n\n", array[i].id, array[i].byte, array[i].str);
	free(array);
	fclose(f1);
}