#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct t_node
{
	char *data;
	struct t_node *next;
}		s_node;


typedef struct
{
	s_node *first;
	int size;
}	s_list;

s_node *create_new(char *str)
{
	s_node *new;

	new = (s_node*)malloc(sizeof(s_node));
	new->next = NULL;
	new->data = (char*)malloc(sizeof(char) * (strlen(str) + 1));
	strcpy(new->data, str);
	return (new);
}

void	push(s_list *list, char *str)
{
	s_node *new;

	list->size++;
	new = create_new(str);
	new->next = list->first;

	list->first = new;
}

void del_el(s_list *list)
{
	s_node *temp;
	s_node *shift;

	if (!list->first)
		return ;
	list->size--;
	temp = list->first;
	shift = temp;
	shift = shift->next;
	list->first = shift;
	free(temp->data);
	free(temp);
}

void	del_N_el(s_list *list, int n)
{
	for (int i = 0; i < n; i++)
		del_el(list);
}

char	*Dequeue(s_list *list)
{
	s_node *shift;
	s_node *temp;
	char *str;

	shift = list->first;
	if (!shift)
		return (NULL);
	if (!shift->next)
	{
		str = shift->data;
		free(shift);
		list->first = NULL;
		return (str);
	}
	while (shift->next->next)
		shift = shift->next;
	str = shift->next->data;
	free(shift->next);
	shift->next = NULL;
	return (str);
}

void	save_lst(s_list *list)
{
	FILE *f;
	s_node *shift;
	char *str;

	if (!(f = fopen("save.txt", "w")))
		exit(-1);
	while ((str = Dequeue(list)))
		fprintf(f, "%s\n", str);
	fclose(f);
}

int main()
{
	char str[30];
	s_list list;

	list.first = NULL;
	list.size = 0;
	while (1)
	{
		scanf("%s", str);
		if (strstr(str, "STOP"))
			break ;
		push(&list, str);
	}
	del_N_el(&list, list.size / 2);
	save_lst(&list);
	del_N_el(&list, list.size);
}