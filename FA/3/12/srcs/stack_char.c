/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_char.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rthai <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/17 11:32:39 by rthai             #+#    #+#             */
/*   Updated: 2019/08/17 11:33:50 by rthai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "header.h"

void	push_stack_char(t_char_st **top, char data)
{
	t_char_st		*temp;

	temp = (t_char_st*)malloc(sizeof(t_char_st));
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

char	pop_stack_char(t_char_st **top)
{
	char		data;
	t_char_st	*temp;

	if (*top == NULL)
		return ('\0');
	data = (*top)->data;
	temp = *top;
	*top = (*top)->next;
	temp = NULL;
	free(temp);
	return (data);
}
