/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rthai <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/18 12:15:20 by rthai             #+#    #+#             */
/*   Updated: 2019/08/18 12:15:26 by rthai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include <stdio.h>

int		my_pow(int a, int b)
{
	int result = 1;

	b++;
	while (--b > 0)
		result *= a;
	return (result);
}

int			calculation(char c, t_int_st **number)
{
	int a;
	int b;

	b = pop_stack_int(number);
	a = pop_stack_int(number);
	if (c == '*')
		return (a * b);
	if (c == '/')
		return (a / b);
	if (c == '%')
		return (a % b);
	if (c == '-')
		return (a - b);
	if (c == '+')
		return (a + b);
	if (c == '^')
		return (my_pow(a, b));	
	return (0);
}

void		operation(char *operation, t_char_st **oper_stack,
			t_int_st **number_stack)
{
	if (*oper_stack != 0 &&
	priority((*oper_stack)->data) < priority(*operation))
	{
		push_stack_char(oper_stack, *operation);
	}
	else
	{
		while (*oper_stack != 0 &&
			priority((*oper_stack)->data) >= priority(*operation))
		{
			push_stack_int(number_stack,
			calculation(pop_stack_char(oper_stack), number_stack));
		}
		push_stack_char(oper_stack, *operation);
	}
}

int		bracket(char *str, t_char_st **oper_stack, t_int_st **number_stack)
{
	if (*str == '(')
		push_stack_char(oper_stack, *str);
	if (*str == ')')
	{
		while (*oper_stack != 0 && (*oper_stack)->data != '(')
		{
			push_stack_int(number_stack,
			calculation(pop_stack_char(oper_stack), number_stack));
		}
		if (!(*oper_stack))
			return (0);
		pop_stack_char(oper_stack);
	}
	return (1);
}

int			eval_expr(char *str, int *result)
{
	t_int_st	*number_stack;
	t_char_st	*oper_stack;
	char		*oper_array;

	oper_stack = 0;
	number_stack = 0;
	oper_array = "*%/-+^";
	while (*str != '\0')
	{
		if (*str == '-' && *(str - 1) <= '0' && *(str - 1) >= '9')
			push_stack_int(&number_stack, create_number(&str));
		if (*str >= '0' && *str <= '9')
			push_stack_int(&number_stack, create_number(&str));
		if (cheack_symbol(oper_array, *str) == 1)
			operation(str, &oper_stack, &number_stack);
		if (*str == '(' || *str == ')')
			if (!(bracket(str, &oper_stack, &number_stack)))
				return (0);
		if (*str != '\0')
			str++;
	}
	while (oper_stack != 0)
	{
		if (!number_stack)
			return (0);
		if (size_stack_int(number_stack) < 2)
			return (0);
		push_stack_int(&number_stack, calculation(pop_stack_char(&oper_stack), &number_stack));
	}
	*result = pop_stack_int(&number_stack);

	return ((number_stack == 0 && oper_stack == 0));
}
