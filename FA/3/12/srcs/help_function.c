/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_function.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rthai <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/17 23:28:41 by rthai             #+#    #+#             */
/*   Updated: 2019/08/17 23:28:44 by rthai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int		create_number(char **str)
{
	int number;
	int sign;

	sign = 1;
	number = 0;
	if (**str == '-')
	{
		sign = -1;
		(*str)++;
	}
	while (**str >= '0' && **str <= '9')
	{
		number = number * 10 + (**str - '0');
		(*str)++;
	}
	return (number * sign);
}

int		priority(char c)
{
	if (c == '^')
		return (4);
	if (c == '*' || c == '%' || c == '/')
		return (3);
	if (c == '+' || c == '-')
		return (2);
	if (c == '(')
		return (1);
	return (0);
}

int		cheack_symbol(char *str, char c)
{
	while (*str != '\0')
	{
		if (*str == c)
			return (1);
		str++;
	}
	return (0);
}

int		size_without_space(char *str)
{
	int result = 0;

	while (*str)
	{
		if (*str != '\t' & *str != ' ')
			result++;
		str++;
	}
	return (result);
}

char	*del_space(char *str)
{
	int		size = size_without_space(str);
	char	*new_str = (char*)malloc(sizeof(char) * (size + 1));
	char	*ptr = new_str;

	for (int i = 0; i < strlen(str); i++)
	{
		if (*str != ' ' && *str != '\t')
			*new_str++ = *str;
		str++;
	}
	return (new_str);
}