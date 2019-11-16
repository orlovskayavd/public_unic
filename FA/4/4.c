#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct 
{
	char	name[30];
	char	surname[30];
	char	patronymic[30];
	char	dob[12];
	char	gender;
	int		income;
}			People;

void	copy(People *a, People *b)
{
	strcpy(a->name, b->name);
	strcpy(a->surname, b->surname);
	strcpy(a->patronymic, b->patronymic);
	strcpy(a->dob, b->dob);
	a->gender = b->gender;
	a->income = b->income;
}

typedef struct s_list
{
	People	man;
	struct s_list	*next;
}			list;

int		mycmp(char *dob1, char *dob2)
{
	int i;

	i = 5;
	while (++i < 10)
		if (dob1[i] != dob2[i])
			return(dob1[i] - dob2[i]);
	i = 2;
	while (++i < 5)
		if (dob1[i] != dob2[i])
			return(dob1[i] - dob2[i]);
	i = -1;		
	while (++i < 2)
		if (dob1[i] != dob2[i])
			return(dob1[i] - dob2[i]);
	return (0);
}
void	print_lst(list **lst)
{
	list *shift;

	shift = *lst;
	while (shift)
	{
		printf("%s %s %s %s %c %d\n", shift->man.surname, shift->man.name, shift->man.patronymic, shift->man.dob, shift->man.gender, shift->man.income);
		shift = shift->next;
	}
	
}
list *lst_create(People new)
{
	list *temp;

	temp = (list*)malloc(sizeof(list));
	temp->next = NULL;
	copy(&temp->man, &new);
	return (temp);
}

void	del_el(list **lst, char *name)
{
	list *shift;
	list *temp;

	if (*lst == NULL)
		return ;
	shift = *lst;
	if (!strcmp(name, shift->man.name))
		*lst = shift->next;
	while (shift->next && strcmp(name, shift->next->man.name))
		shift = shift->next;
	if (shift->next && !strcmp(name, shift->next->man.name))
	{
		temp = shift->next;
		shift->next = shift->next->next;
		free(temp);
	}
}

void	del_all(list **lst)
{
	list *shift = (*lst)->next;
	list *temp = *lst;

	
	while (shift)
	{
		free(temp);
		temp = shift;
		shift = shift->next;
	}
	*lst = NULL;
}

list	*search(list **lst, char *name)
{
	list *shift = *lst;

	while (shift && strcmp(name, shift->man.name))
		shift = shift->next;
	return (shift);
}

void	push_el(list **lst, People new)
{
	list *shift;
	list *temp;

	if (*lst == NULL)
	{
		*lst = lst_create(new);
		return ;
	}
	shift = *lst;
	if (mycmp(shift->man.dob, new.dob) < 0)
	{
		temp = lst_create(new);
		temp->next = shift;
		*lst = temp;
		return ;
	}
	while (shift->next && mycmp(shift->next->man.dob, new.dob) > 0)
		shift = shift->next;
	temp = lst_create(new);
	temp->next = shift->next;
	shift->next = temp;
}



int		push_list(FILE *f, list **lst)
{
	int flag = 0;
	char c;
	People new;
	char *ptr_name = new.name;
	char *ptr_surname = new.surname;
	char *ptr_patronymic = new.patronymic;
	char *ptr_dob = new.dob;
	new.income = 0;

	while ((c = fgetc(f)))
	{
		if (c == ' ')
		{
			flag++;
			continue ;
		}
		if (c == '\n' || c == EOF)
		{
			*ptr_name = 0;
			*ptr_surname = 0;
			*ptr_patronymic = 0;
			*ptr_dob = 0;
			push_el(lst, new);
			if (c == EOF)
				break ;
			ptr_name = new.name;
			ptr_surname = new.surname;
			ptr_patronymic = new.patronymic;
			ptr_dob = new.dob;
			new.income = 0;
			flag = 0;
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
			*ptr_dob++ = c;
			break;
		case (4):
			new.gender = c;
			break;
		case (5):
			new.income = 10 * new.income + c - '0';
			break;	
		default:
			break;
		}
	}
}

void print_error(int id, char *file)
{
	if (id == 0)
		printf("No file: %s\n", file);
	exit(id);
}

void	save_lst(list **lst)
{
	list *shift = *lst;
	FILE *f;

	if(!(f = fopen("save.txt", "w")))
		print_error(0, "save.txt");
	while (shift)
	{
		fprintf(f, "%s %s %s %s %c %d\n", shift->man.surname, shift->man.name, shift->man.patronymic, shift->man.dob, shift->man.gender, shift->man.income);
		shift = shift->next;
	}
	fclose(f);
}

int main(int argc, char **argv)
{
	FILE *f;
	list *lst = NULL;
	list *lst1;

	if (!(f = fopen(argv[1], "r")))
		print_error(0, argv[1]);
	push_list(f, &lst);
	print_lst(&lst);
	lst1 = search(&lst, "Roman");
	printf("%s %s\n", lst1->man.name, lst1->man.surname);
	del_el(&lst, "ertret");
	print_lst(&lst);
	save_lst(&lst);
	del_all(&lst);
	fclose(f);
}