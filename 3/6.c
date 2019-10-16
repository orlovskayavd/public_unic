#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct	s_student
{
	char	name[30];
	char	surname[30];
	char	patronymic[30];
	char	group[30];
	int		exam_1;
	int		exam_2;
	int		exam_3;
	int		exam_4;
	int		exam_5;
	int		exam_mean;

}				Student;

int		push_struct(Student **stud, FILE *f1)
{
	int flag = 0;
	char c;
	char *ptr_name;
	char *ptr_surname;
	char *ptr_patronymic;
	char *ptr_group;
	int i = 0;
	int size = 10;

	*stud = (Student*)malloc(sizeof(Student) * (size + 1));
	ptr_name = (*stud)[i].name;
	ptr_surname = (*stud)[i].surname;
	ptr_patronymic = (*stud)[i].patronymic;
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
			(*stud)[i].exam_mean = ((*stud)[i].exam_1 + (*stud)[i].exam_2 + (*stud)[i].exam_3 + (*stud)[i].exam_4 + (*stud)[i].exam_5) / 5.;
			i++;
			*ptr_name = 0;
			*ptr_surname = 0;
			*ptr_patronymic = 0;
			*ptr_group = 0;
			if (i >= size)
			{
				size += 10;
				*stud = (Student*)realloc((*stud), sizeof(Student) * size);
			}
			flag = 0;
			ptr_name = (*stud)[i].name;
			ptr_surname = (*stud)[i].surname;
			ptr_patronymic = (*stud)[i].patronymic;
			ptr_group = (*stud)[i].group;
			continue ;
		}
		switch (flag)
		{
		case (0):
			*ptr_surname++ = c;
			break;
		case (1):
			*ptr_name++ = c;
			break;
		case (2):
			*ptr_patronymic++ = c;
			break;
		case (3):
			*ptr_group++ = c;
			break;
		case (4):
			(*stud)[i].exam_1 = c - '0';
			break;
		case (5):
			(*stud)[i].exam_2 = c - '0';
			break;
		case (6):
			(*stud)[i].exam_3 = c - '0';
			break;
		case (7):
			(*stud)[i].exam_4 = c - '0';
			break;
		case (8):
			(*stud)[i].exam_5 = c - '0';
			break;
		default:
			break;
		}
	}
	return (i);
}

void	print_struct(Student *stud, int size)
{
	int mean = 0;


	for (int i = 0; i < size; i++)
	{
		printf("surname = %s\nname = %s\npatronymic = %s\ngroup = %s\nexam_mean = %d\n\n",
		stud[i].surname, stud[i].name, stud[i].patronymic, stud[i].group, stud[i].exam_mean);
		mean += stud[i].exam_mean;
	}
	mean /= size;
	printf("--------------------------------//--------------------------------------\n");
	for (int i = 0; i < size; i++)
		if (mean <= stud[i].exam_mean)
			printf("surname = %s name = %s\n\n", stud[i].surname, stud[i].name);
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
	print_struct(stud, size);
	free(stud);
	fclose(f1);
}