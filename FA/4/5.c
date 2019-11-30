#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX(x, y) x > y ? x : y

typedef struct
{
	int len;
	char *str;
}	min_max;

typedef struct
{
	int count;
	char *str;
}		count_char;


typedef struct	t_tree
{
	struct t_tree *left;
	struct t_tree *right;
	char *data;
	int count;
}		s_tree;

s_tree *create_el(char *str)
{
	s_tree *new;

	new = (s_tree*)malloc(sizeof(s_tree));
	new->left = NULL;
	new->right = NULL;
	new->count = 1;
	new->data = (char*)malloc(sizeof(char) * (strlen(str) + 1));
	strcpy(new->data, str);
	return (new);
}

void	insert_el(s_tree **tree, char *str)
{
	s_tree *shift = *tree;

	if (!shift)
		*tree = create_el(str);
	while (shift)
	{
		if (strcmp(shift->data, str) > 0)
			if (shift->left)
				shift = shift->left;
			else
			{
				shift->left = create_el(str);
				return ;
			}
		if (strcmp(shift->data, str) < 0)
			if (shift->right)
				shift = shift->right;
			else
			{
				shift->right = create_el(str);
				return ;
			}
		if (strcmp(shift->data, str) == 0)
		{
			shift->count++;
			return ;
		}
	}
}

s_tree *create_el_new(char *str, int count)
{
	s_tree *new;

	new = (s_tree*)malloc(sizeof(s_tree));
	new->left = NULL;
	new->right = NULL;
	new->count = count;
	new->data = (char*)malloc(sizeof(char) * (strlen(str) + 1));
	strcpy(new->data, str);
	return (new);
}

void	insert_el_new(s_tree **tree, char *str, int count)
{
	s_tree *shift = *tree;

	if (!shift)
		*tree = create_el_new(str, count);
	while (shift)
	{
		if (shift->count > count)
			if (shift->left)
				shift = shift->left;
			else
			{
				shift->left = create_el_new(str, count);
				return ;
			}
		if (shift->count <= count)
			if (shift->right)
				shift = shift->right;
			else
			{
				shift->right = create_el_new(str, count);
				return ;
			}
	}
}

void	search_long_and_short(s_tree *tree, min_max *min, min_max *max)
{
	if (!tree)
		return ;
	if (strlen(tree->data) > max->len)
	{
		max->len = strlen(tree->data);
		max->str = tree->data;
	}
	if (strlen(tree->data) < min->len)
	{
		min->len = strlen(tree->data);
		min->str = tree->data;
	}
	search_long_and_short(tree->left, min, max);
	search_long_and_short(tree->right, min, max);
}

int		deep_tree(s_tree *tree)
{
	int max;

	if (!tree)
		return (0);
	max = MAX(deep_tree(tree->left), deep_tree(tree->right));
	return (max + 1);
}

void	save_tree_help(s_tree *tree, FILE *f)
{
	if (!tree)
		return ;
	fprintf(f, "%s %d %d %d\n", tree->data, tree->count, tree->left != NULL, tree->right != NULL);
	save_tree_help(tree->left, f);
	save_tree_help(tree->right, f);
}

void	save_tree(s_tree *tree)
{
	FILE *f;

	if (!(f = fopen("save.txt", "w")))
		exit(-1);
	save_tree_help(tree, f);
	fprintf(f, "END\n");
	fclose(f);
}

void	push_new_tree(s_tree *tree, s_tree **new)
{
	if (!tree)
		return ;
	insert_el_new(new, tree->data, tree->count);
	push_new_tree(tree->left, new);
	push_new_tree(tree->right, new);
	free(tree->data);
	free(tree);
}

s_tree		*load_tree(s_tree *tree, FILE *f)
{
	char str[20];
	int count;
	int l, r;

	fscanf(f, "%s %d %d %d", str, &count, &l, &r);
	if (tree == NULL)
		tree = create_el_new(str, count);

	if (l)
		tree->left = load_tree(tree->left, f);

	if (r)
		tree->right = load_tree(tree->right, f);

	return tree;
}

void print_tree(s_tree *tree, int level)
{
	if (!tree)
		return ;
	print_tree(tree->left, level + 1);
	for (int i = 0; i < level; i++)
		printf("-");
	printf("%s: %d\n", tree->data, tree->count);
	print_tree(tree->right, level + 1);
}

void	print_max_long(s_tree *tree, int *n)
{
	if (!tree)
		return ;
	print_max_long(tree->right, n);
	if (*n > 0)
	{
		printf("%s: %d\n", tree->data, tree->count);
		(*n)--;
	}
	print_max_long(tree->left, n);
}

void	free_all(s_tree *tree)
{
	if (!tree)
		return ;
	free_all(tree->left);
	free_all(tree->right);
	free(tree->data);
	free(tree);
}

int main(int argc, char **argv)
{
	FILE *f;
	char str[30];
	char *ptr = str;
	char c;
	s_tree *new_tree = NULL, *tree = NULL, *tree_l = NULL; 
	int n;
	min_max min, max;

	if (!(f = fopen(argv[1], "r")))
		exit(-1);
	while (c = fgetc(f))
	{
		if (c != ' ' && c != EOF && c != '\n')
			*ptr++ = c;
		else if (ptr != str)
		{
			*ptr = 0;
			insert_el(&tree, str);
			ptr = str;
		}
		if (c == EOF)
			 break ;
	}
	print_tree(tree, 0);
	push_new_tree(tree, &new_tree);
	printf("\n");
	print_tree(new_tree, 0);
	n = 25;
	printf("\n");
	print_max_long(new_tree, &n);//depth
	printf("%d\n", deep_tree(new_tree));
	min.len = max.len = strlen(new_tree->data);
	min.str = max.str = new_tree->data;
	search_long_and_short(new_tree, &min, &max);
	printf("%s %s\n", min.str, max.str);
	save_tree(new_tree);
	printf("load: \n");
	FILE *f1;

	if (!(f1 = fopen("save.txt", "r")))
	{
		exit(-1);
	}
	tree_l = load_tree(tree_l, f1);
	print_tree(tree_l, 0);
	free_all(tree_l);
	free_all(new_tree);
}