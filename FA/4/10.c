#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <string.h>
#include <unistd.h>




typedef struct	t_tree
{
	char val;
	int neg;
	struct t_tree *left;
	struct t_tree *right;

}				s_tree;

typedef struct	st_tree
{
	s_tree *tree;
	struct st_tree *next;
}				stack_tree;

void push(stack_tree **head, stack_tree *tree)
{
	stack_tree *tmp = malloc(sizeof(stack_tree));
	
	if (tmp == NULL)
		exit(11);
	
	tmp->next = *head;
	tmp->tree = (s_tree*)malloc(sizeof(s_tree));
	tmp->tree = tree;
	*head = tmp;
}

stack_tree *pop(stack_tree **head)
{
	stack_tree *out;
	s_tree *tree;

	if (*head == NULL)
		exit(12);

	out = *head;
	*head = (*head)->next;
	tree = out->tree;
	free(out);
	return tree;
}

s_tree *peek(stack_tree *head)
{
	if (head == NULL)
		exit(12);

	return head->tree;
}

typedef struct
{
	char data[200];
	int size;
} Stack;

int prior(char c);
s_tree *addtree(char c, int n);
s_tree *treest(char c, s_tree *right, s_tree *left);
int fun(int n, int i);
int calc(int leftop, int rightop, const char oper);

void pushs(Stack *stack, char c)
{
	if (stack->size >= 200)
		exit(21);

	stack->data[stack->size] = c;
	stack->size++;
}

char pops(Stack *stack)
{
	if (stack->size == 0)
		exit(22);

	stack->size--;
	return stack->data[stack->size];
}


int		calc_tree(int *array, s_tree *tree)
{
	if (isalpha(tree->val))
		return (array[tree->val - 'a']);
	return (calc(calc_tree(array, tree->left), calc_tree(array, tree->right), tree->val));
}

char peeks(Stack *stack)
{
	return stack->data[stack->size - 1];
}

void treeprint(s_tree *tree, int n)
{
	if (tree->left)
		treeprint(tree->left, n + 1);

	for (int i = 0; i < n * 3; i++) 
		printf(" ");
	
	if (tree->neg)
		printf("~");
	printf("%c", tree->val);
	if (tree->val == '<' || tree->val == '+' || tree->val == '-')
		printf(">");
	printf("\n");

	if (tree->right)
		treeprint(tree->right, n + 1);
}

void treetostack(s_tree *tree, int i, char* letters, Stack *stack)
{
	size_t j;

	if (tree->right)
		treetostack(tree->right, i, letters, stack);

	if (tree->left)
		treetostack(tree->left, i, letters, stack);

	if (isalpha(tree->val))
	{
		for(j = 0; j < strlen(letters); j++)
			if(tree->val == letters[j])
				break;
		pushs(stack, (i >> j & 1)  + '0');
	}
	else
	{
		pushs(stack, tree->val);
	}
}

void printstack(Stack stack, char *arr)
{
	while (stack.size > 0)
	{
		*arr++ = peeks(&stack);
		pops(&stack);
	}
	*arr = 0;
}

// void reversestr(char *str) 
// { 
// 	int n = strlen(str); 
// 	char buf;

// 	for (int i = 0; i < n / 2; i++)
// 	{
// 		buf = str[i];
// 		str[i] = str[n - i - 1];
// 		str[n - i - 1] = buf;
// 	}
// } 

void	push_array(int *array, int number, int count, char *LETTERS)
{
	for (int i = 0; i < count; i++)
	{
		array[tolower(*LETTERS) - 'a'] = (number >> i) & 1;
		printf("%d", (number >> i) & 1);
		LETTERS++;
	}
	
}

int main()
{
	FILE *fIn;
	stack_tree *head = NULL;
	Stack stack;
	stack.size = 0;
	size_t count = 0;
	char c, LETTERS[26] = {0};
	char array[256] = {0}, *arr = array;
	int n;


	if((fIn = fopen("10.txt", "r")) == 0)
	{
		printf("There is a problem with input file!\n");
		exit(1);
	}

	while((c = fgetc(fIn)) != EOF)
	{	
		n = 0;

		if (c == '~')
		{
			c = fgetc(fIn);
			n = 1;
		}

		if (c == '<' || c == '+' || c == '-')
			fgetc(fIn);

		if (isalnum(c))
		{
			if (isalpha(c) && !(strstr(LETTERS, &c)))
				LETTERS[count++] = c;
			push(&head, addtree(c, n));
		}
		else if (c != ')' && (stack.size == 0 || prior(c) > prior(peeks(&stack)) || c == '(' || peeks(&stack) == '('))
		{
			pushs(&stack, c);
		}
		else
		{
			while(stack.size != 0 && ((c == ')' && peeks(&stack) != '(') || prior(peeks(&stack)) >= prior(c)))
			{
				s_tree *new = treest(pops(&stack), pop(&head), pop(&head));
				push(&head, new);
			}
			if (peeks(&stack) == '(' && c == ')')
				pops(&stack);
			if (c != ')')
				pushs(&stack, c);
		}
	}
	while(stack.size != 0)
	{
		s_tree *new = treest(pops(&stack), pop(&head), pop(&head));
		push(&head, new);
	}
	

	
	treeprint(peek(head), 0);
	int change[26];
	printf("%s\n", LETTERS);
	for (int i = 0; i < pow(2, count); i++)
	{
		push_array(change, i, count, LETTERS);
		printf ("%d\n", calc_tree(change, peek(head)));
	}
	
	
	fclose(fIn);
	return 0;
}

int calc(int leftop, int rightop, const char oper)
{
	switch (oper)
	{
		case '|':
			return leftop | rightop;
		case '-':
			return !(leftop) | rightop;
		case '<':
			return !(leftop == rightop);
		case '=':
			return leftop == rightop;
		case '&': 
			return leftop & rightop;
		case '+':
			return leftop & (!rightop);
		case '!':
			return !(leftop & rightop);	
		case '?':
			return !(leftop | rightop);
		case '~':
			return !leftop;
	}
}



int prior(char c)
{
	if (c == '~')
		return 3;
	if (c == '?' || c == '!' || c == '+' || c == '&')
		return 2;
	if (c == '|' || c == '-' || c == '<' || c == '=')
		return 1;
}

s_tree *addtree(char c, int n)
{
	s_tree *tree = (s_tree*)malloc(sizeof(s_tree));
	tree->val = c;
	if (!n)
		tree->neg = 0;
	else
		tree->neg = 1;
	tree->left = NULL;
	tree->right = NULL;
	return tree;
}

s_tree *treest(char c, s_tree *left, s_tree *right)
{
	s_tree *tree = (s_tree*)malloc(sizeof(s_tree));
	tree->val = c;
	tree->neg = 0;
	tree->left = left;
	tree->right = right;
	return tree;
}