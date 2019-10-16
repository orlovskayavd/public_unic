/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rthai <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/17 11:59:31 by rthai             #+#    #+#             */
/*   Updated: 2019/08/18 21:51:17 by rthai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include <stdio.h>
#define BUFF_SIZE 100

int		main(int argc, char **argv)
{
	FILE *f1;
	char buff[BUFF_SIZE];
	int result;
	FILE *f2;
	int i;
	for (int i = 1; i < argc; i++)
	{
		if (!(f1 = fopen(argv[i], "r")))
		{
			printf("file: %s - ERROR\n", argv[i]);
			continue ;
		}
		argv[i][0] = '-';
		if (!(f2 = fopen(argv[i], "w")))
		{
			printf("file: %s - ERROR\n", argv[i]);
			continue ;
		}
		printf("name file: %s\n", argv[i]);
		int j = 1;
		while ((fgets(buff, BUFF_SIZE, f1)))
		{	
			if (eval_expr(buff, &result))
				printf("%s %d\n", buff, result);
			else
				fprintf(f2, "number: %d\n%s\n\n", j, buff);
		}
		fclose(f2);
		fclose(f1);
	}
	
	return (0);
}
