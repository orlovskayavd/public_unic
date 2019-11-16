#include <stdio.h>
#include <stdlib.h>
#define NUMBER_PEOPLE 100

typedef struct	s_people
{
	int		id;
	char	name[30];
	char	surname[30];
	int		salary;
}				Employee;

int		push_struct(Employee people[NUMBER_PEOPLE], FILE *f1)
{
	int flag = 0;
	char c;
	Employee *ptr = people;
	char *ptr_name = ptr->name;
	char *ptr_surname = ptr->surname;
	int size = 1;

	ptr->id = 0;
	ptr->salary = 0;
	while ((c = fgetc(f1)) != EOF)
	{
		if (c == ' ')
		{
			flag++;
			continue ;
		}
		if (c == '\n')
		{
			*ptr_name = 0;
			*ptr_surname = 0;
			ptr++;
			size++;
			flag = 0;
			ptr->id = 0;
			ptr_name = ptr->name;
			ptr_surname = ptr->surname;
			ptr->salary = 0;
			continue ;
		}
		switch (flag)
		{
		case (0):
			ptr->id = ptr->id * 10 + (c - '0');
			break;
		case (1):
			*ptr_name++ = c;
			break;
		case (2):
			*ptr_surname++ = c;
			break;
		case (3):
			ptr->salary = ptr->salary * 10 + (c - '0');
			break;
		default:
			break;
		}
	}
	return (size - 1);
}

void	sort(Employee people[NUMBER_PEOPLE], int size)
{
	int i = 0;
	Employee temp;

	while(i < size - 1)
	{
		temp = people[i];
		if (temp.salary > people[i + 1].salary)
		{
			people[i] = people[i + 1];
			people[i + 1] = temp;
			i = 0;
			continue ;
		}
		i++;
	}
}

void	print_struct(Employee people[NUMBER_PEOPLE], int size)
{
	for (int i = 0; i < size; i++)
		printf("id = %d\nname = %s\nsurname = %s\nsalary = %d\n\n", people[i].id, people[i].name, people[i].surname, people[i].salary);
}

int main(int argc, char **argv)
{
	FILE	*f1;
	char	c;
	int		flag = 0;
	Employee people[NUMBER_PEOPLE];
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
	size = push_struct(people, f1);
	sort(people, size);
	print_struct(people, size);
	fclose(f1);
}