#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define BUF_SIZE 200

typedef struct t_priority
{
	struct t_priority *next;
	int priority;
	char *data;
}		s_priority;

s_priority *new_prior(int priority, char *data)
{
	s_priority *new;

	new = (s_priority*)malloc(sizeof(s_priority));
	new->next = NULL;
	new->priority = priority;
	new->data = (char*)malloc(sizeof(char) * (strlen(data) + 1));
	strcpy(new->data, data);
	return (new);
}

void Enqueue(s_priority **prior, int priority, char *data)
{
	s_priority *new;
	s_priority *shift;

	new = new_prior(priority, data);
	shift = *prior;
	if (!shift)
		*prior = new;
	while (shift->next)
		shift = shift->next;
	shift->next = new;
}

char	*Dequeue(s_priority **prior)
{
	char *str;
	s_priority *temp;

	temp = *prior;
	if (!temp)
		return (NULL);
	*prior = (*prior)->next;
	str = temp->data;
	free(temp);
	return (str);
}

void	EnqueuePriority(s_priority **prior, int priority, char *data)
{
	s_priority *new;
	s_priority *shift = *prior;

	new = new_prior(priority, data);
	if (!*prior)
	{
		*prior = new;
		return ;
	}
	if (new->priority < shift->priority)
	{
		new->next = *prior;
		*prior = new;
	}
	while (shift->next && shift->next->priority < new->priority)
		shift = shift->next;
	new->next = shift->next;
	shift->next = new;
}

int		my_strlen(char *str)
{
	int size = 0;
	while (str[size++]);
	return(size);
}

void	parser(s_priority **prior, char *str)
{
	int priority = 0;

	str = strchr(str, '=');
	while (*++str != ' ')
		priority = priority * 10 + *str -'0';
	str = strchr(str, '=');
	str += 2;
	str[strlen(str) - 2] = 0;
	EnqueuePriority(prior, priority, str);
}

void	print_prior(s_priority *prior)
{
	while (prior)
	{
		printf("%d %s\n", prior->priority, prior->data);
		prior = prior->next;
	}
}

void print_error(int id, char *name)
{
	if (id == 0)
		printf("No file: %s\n", name);
	exit(id);
}

void	del_all(s_priority **lst)
{
	s_priority *shift = (*lst)->next;
	s_priority *temp = *lst;

	
	while (shift)
	{
		free(temp);
		temp = shift;
		shift = shift->next;
	}
	*lst = NULL;
}

int main(int argc, char **argv)
{
	FILE *f;
	s_priority *prior = NULL;
	char buf[1000];
	char *temp = buf; 

	for (int i = 1; i < argc; i++)
	{
		f = fopen(argv[i], "r");
		while ((temp = fgets(buf, 1000, f)))
		{
			parser(&prior, temp);
		}
		fclose(f);
	}
	print_prior(prior);
	// Enqueue(&prior, 1, "asdf");
	// print_prior(prior);
	del_all(&prior);
}