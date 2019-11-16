#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define	MAX(a, b) a > b ? a : b

int		replace_int(char c)
{
	if (isalpha(c))
		return (tolower(c) - 'a' + 10);
	if (isdigit(c))
		return (c - '0');
	if (c == 0)
		return (0);
	// printf("c = %d", c);
	printf("ERROR\n");
	exit(1);
}

char	replace_char(int a)
{
	if (a < 10)
		return (a + '0');
	return (a - 10 + 'a');
}

void	strrev(char *str)
{
	char *ptr_str = str;
	char temp;

	while (*str)
		str++;
	str--;
	while (str > ptr_str)
	{
		temp = *ptr_str;
		*ptr_str = *str;
		*str = temp;
		str--;
		ptr_str++;
	}
}

char *sum_help(int base, char *str, char *str1)
{
	char 	*result;
	char 	*ptr;
	int		balance = 0;
	int		size;

	result = (char*)malloc(sizeof(char) * ((MAX(strlen(str), strlen(str1))) + 3));
	ptr = result;
	strrev(str);
	strrev(str1);
	while(*str || *str1)
	{
		*ptr = replace_char((replace_int(*str) + replace_int(*str1) + balance) % base);
		balance = (replace_int(*str) + replace_int(*str1) + balance) / base;
		ptr++;
		if (*str)
			str++;
		if (*str1)
			str1++;
	}
	if (balance)
		*ptr++ = replace_char(balance);
	*ptr = 0;
	strrev(result);
	return (result);
}

char *sum(int base, int n, ...)
{
	char		*temp;
	char		*result;
	va_list		ptr;

	va_start(ptr, n);
	result = sum_help(base, va_arg(ptr, char*), va_arg(ptr, char*));
	for (int i = 0; i < n - 2; i++)
	{
		temp = sum_help(base, result, va_arg(ptr, char*));
		free(result);
		result = temp;
	}
	va_end(ptr);
	return(result);
}

int		main()
{
	char str[] = "999";
	char str2[] = "999";
	char str3[] = "1234";
	char str4[] = "1234";
	char *result;

	result = sum(10, 2, str, str2);
	printf("%s\n", result);
	free(result);
}