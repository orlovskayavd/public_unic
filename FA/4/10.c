#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <string.h>
#include <unistd.h>

typedef unsigned long int UINT32;

typedef struct Tree
{
	char val;
	int neg;
	struct Tree *left;
	struct Tree *right;

}Tree, *PTree;

typedef struct Node
{
	PTree tree;
	struct Node *next;
}Node, *PNode;

void push(PNode *head, PTree tree)
{
	PNode tmp = malloc(sizeof(PNode));
	
	if (tmp == NULL)
		exit(11);
	
	tmp->next = *head;
	tmp->tree = (PTree)malloc(sizeof(Tree));
	tmp->tree = tree;
	*head = tmp;
}

PTree pop(PNode *head)
{
	PNode out;
	PTree tree;

	if (*head == NULL)
		exit(12);

	out = *head;
	*head = (*head)->next;
	tree = out->tree;
	free(out);
	return tree;
}

PTree peek(const PNode head)
{
	if (head == NULL)
		exit(12);

	return head->tree;
}

typedef struct Stack
{
	char data[200];
	int size;
} Stack;

void pushs(Stack *stack, char c)
{
	if (stack->size >= 200)
	{
		exit(21);
	}

	stack->data[stack->size] = c;
	stack->size++;
}

char pops(Stack *stack)
{
	if (stack->size == 0)
	{
		exit(22);
	}

	stack->size--;
	return stack->data[stack->size];
}

char peeks(Stack *stack)
{
	return stack->data[stack->size - 1];
}

void treeprint(PTree tree, int n)
{
	if (tree->left)
	{
		treeprint(tree->left, n + 1);
	}

	for (int i = 0; i < n * 3; i++) 
		printf(" ");
	
	if (tree->neg)
		printf("~");
	printf("%c", tree->val);
	if (tree->val == '<' || tree->val == '+' || tree->val == '-')
		printf(">");
	printf("\n");

	if (tree->right)
	{
		treeprint(tree->right, n + 1);
	}
}

void treetostack(PTree tree, UINT32 i, char* letters, Stack *stack)
{
	size_t j;

	if (tree->right)
	{
		treetostack(tree->right, i, letters, stack);
	}

	if (tree->left)
	{
		treetostack(tree->left, i, letters, stack);
	}

	if (isalpha(tree->val))
	{
		for(j = 0; j < strlen(letters); j++)
			if(tree->val == letters[j])
				break;
		//printf("%c ", (i >> j & 1) + '0');
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

void reversestr(char *str) 
{ 
	int n = strlen(str); 
	char buf;

	for (int i = 0; i < n / 2; i++)
	{
		buf = str[i];
		str[i] = str[n - i - 1];
		str[n - i - 1] = buf;
	}
} 

int prior(char c);
PTree addtree(char c, int n);
PTree treest(char c, PTree right, PTree left);
int fun(int n, int i);
int calc(int leftop, int rightop, const char oper);

int main()
{
	FILE *fIn;
	PNode head = NULL;
	Stack stack;
	stack.size = 0;
	size_t count = 0;
	char c, LETTERS[26] = {0};
	int n;


	if((fIn = fopen("in10.txt", "r")) == 0)
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
				PTree new = treest(pops(&stack), pop(&head), pop(&head));
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
		PTree new = treest(pops(&stack), pop(&head), pop(&head));
		push(&head, new);
	}

	treeprint(peek(head), 0);

	/*int arr[2];

	for (int i = 1; i <= 2; i++)
	{
		arr[i - 1] = fun(2, i);
		printf("%d\n", fun(2, i));
	}

	printf("%d\n", calc(arr[0], arr[1], '&'));*/
	char array[256] = {0}, *arr = array;
	printf("%lf\n", pow(2, count));
	for (UINT32 i = 0; i < pow(2, count); i++)
	{
		stack.size = 0;
		arr = array;
		treetostack(peek(head), i, LETTERS, &stack);
		printstack(stack, arr);
		reversestr(array);
		printf("%s\n", array);

		
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

int fun(int n, int i)
{
	int result = 0;
	int k = pow(2, n) / pow (2, i);
	//printf("%d %f\n", k, (pow(2, i) / 2));

	for (int j = 0; j < pow(2, i - 1); j++)
	{
		result <<= k;
		result |= (int)pow(2, k) - 1;
		result <<= k;
	}

	return result;
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

PTree addtree(char c, int n)
{
	PTree tree = (PTree)malloc(sizeof(Tree));
	tree->val = c;
	if (!n)
		tree->neg = 0;
	else
		tree->neg = 1;
	tree->left = NULL;
	tree->right = NULL;
	return tree;
}

PTree treest(char c, PTree left, PTree right)
{
	PTree tree = (PTree)malloc(sizeof(Tree));
	tree->val = c;
	tree->neg = 0;
	tree->left = left;
	tree->right = right;
	return tree;
}