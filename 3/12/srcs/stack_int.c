/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_int.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rthai <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/17 12:30:39 by rthai             #+#    #+#             */
/*   Updated: 2019/08/17 12:30:41 by rthai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "header.h"

void	push_stack_int(t_int_st **top, int data)
{
	t_int_st		*temp;

	temp = (t_int_st*)malloc(sizeof(t_int_st));
	temp->data = data;
	if (*top == 0)
	{
		temp->next = NULL;
		*top = temp;
		return ;
	}
	temp->next = *top;
	*top = temp;
}

int		pop_stack_int(t_int_st **top)
{
	int			data;
	t_int_st	*temp;

	if (*top == NULL)
		return ('\0');
	data = (*top)->data;
	temp = *top;
	*top = (*top)->next;
	temp = NULL;
	free(temp);
	return (data);
}

int		size_stack_int(t_int_st *top)
{
	int size = 0;
	while (top)
	{
		size++;
		top = top->next;
	}
	return (size);
}
