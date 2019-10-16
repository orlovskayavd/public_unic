/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rthai <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/17 12:03:08 by rthai             #+#    #+#             */
/*   Updated: 2019/08/17 12:03:10 by rthai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

typedef struct		s_char_st
{
	char				data;
	struct s_char_st	*next;
}					t_char_st;
typedef struct		s_int_st
{
	int					data;
	struct s_int_st		*next;
}					t_int_st;

int					pop_stack_int(t_int_st **top);
void				push_stack_int(t_int_st **top, int data);
int					create_number(char **str);
int					create_number(char **str);
int					priority(char c);
int					cheack_symbol(char *str, char c);
int					calculation(char c, t_int_st **number);
int					size_stack_int(t_int_st *top);
int					operation(char *operation,
					t_char_st **oper_stack, t_int_st **number_stack);
int					bracket(char *str, t_char_st **oper_stack,
							t_int_st **number_stack);
int					eval_expr(char *str, int *result);
char				pop_stack_char(t_char_st **top);
void				push_stack_char(t_char_st **top, char data);

#endif
