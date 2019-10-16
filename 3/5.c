#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct	s_student
{
	int		id;
	char	name[30];
	char	surname[30];
	char	group[30];
}				Student;

int		push_struct(Student **stud, FILE *f1)
{
	int flag = 0;
	char c;
	char *ptr_name;
	char *ptr_surname;
	char *ptr_group;
	int i = 0;
	int size = 10;

	*stud = (Student*)malloc(sizeof(Student) * (size + 1));
	(*stud)[i].id = 0;
	ptr_name = (*stud)[i].name;
	ptr_surname = (*stud)[i].surname;
	ptr_group = (*stud)[i].group;
	while ((c = fgetc(f1)) != EOF)
	{
		if (c == ' ')
		{
			flag++;
			continue ;
		}
		if (c == '\n')
		{
			i++;
			*ptr_name = 0;
			*ptr_surname = 0;
			*ptr_group = 0;
			if (i >= size)
			{
				size += 10;
				*stud = (Student*)realloc((*stud), sizeof(Student) * (size + 1));
			}
			flag = 0;
			(*stud)[i].id = 0;
			ptr_name = (*stud)[i].name;
			ptr_surname = (*stud)[i].surname;
			ptr_group = (*stud)[i].group;
			continue ;
		}
		switch (flag)
		{
		case (0):
			(*stud)[i].id = (*stud)[i].id * 10 + (c - '0');
			break;
		case (1):
			*ptr_name++ = c;
			break;
		case (2):
			*ptr_surname++ = c;
			break;
		case (3):
			*ptr_group++ = c;
			break;
		default:
			break;
		}
	}
	return (i);
}

void	search_for_id(Student *stud, int id, int size)
{
	for (int i = 0; i < size; i++)
	{
		if (stud[i].id == id)
			printf("id = %d\nname = %s\nsurname = %s\ngroup = %s\n\n", stud[i].id, stud[i].name, stud[i].surname, stud[i].group);
	}
	
}

void	search_for_surname(Student *stud, char *surname, int size)
{
	for (int i = 0; i < size; i++)
	{
		if (!(strcmp(surname, stud[i].surname)))
			printf("id = %d\nname = %s\nsurname = %s\ngroup = %s\n\n", stud[i].id, stud[i].name, stud[i].surname, stud[i].group);
	}
	
}

void	search_for_name(Student *stud, char *name, int size)
{
	for (int i = 0; i < size; i++)
	{
		if (!(strcmp(name, stud[i].name)))
			printf("id = %d\nname = %s\nsurname = %s\ngroup = %s\n\n", stud[i].id, stud[i].name, stud[i].surname, stud[i].group);
	}
	
}

void	search_for_group(Student *stud, char *group, int size)
{
	for (int i = 0; i < size; i++)
	{
		if (!(strcmp(group, stud[i].group)))
			printf("id = %d\nname = %s\nsurname = %s\ngroup = %s\n\n", stud[i].id, stud[i].name, stud[i].surname, stud[i].group);
	}
	
}
void	print_struct(Student *stud, int size)
{
	for (int i = 0; i < size; i++)
		printf("id = %d\nname = %s\nsurname = %s\ngroup = %s\n\n", stud[i].id, stud[i].name, stud[i].surname, stud[i].group);
}



int		main(int argc, char **argv)
{
	Student *stud = NULL;
	FILE *f1;
	int size;

	if (argc != 2)
	{
		printf("ERROR\n");
		return (0);
	}
	if (!(f1 = fopen(argv[1], "r")))
	{
		printf("No file\n");
		return (0);
	}
	size = push_struct(&stud, f1);
	// print_struct(stud, size);
	search_for_group(stud, "M80-410B", size);
	search_for_name(stud, "sdfxcsdfg", size);
	search_for_surname(stud, "rtyety", size);
	search_for_id(stud, 4, size);
	free(stud);
	fclose(f1);
}