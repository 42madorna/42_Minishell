/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madorna- <madorna-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 16:50:18 by madorna-          #+#    #+#             */
/*   Updated: 2022/02/11 07:24:03 by madorna-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** builtin: exit
** exit writes always "exit\n" and then checks:
** 	1. Numeric first argument
** 	2. Arguments can not be >= 3
** If there is not a numeric argument, then calls exit(255), if the argument
** 	is valid, it calls exit using ft_atoi. If no arguments are supplied, then,
** 	exit(0) is called.
** Keep in mind that exit is not meant to take options as the subject says !
*/

int
	ft_exit(int argc, char **argv, t_list *env)
{
	int		i;

	(void)env;
	i = -1;
	printf("exit\n");
	if (argc == 1)
		exit(0);
	while (argv[1][++i])
	{
		if (ft_isalpha(argv[1][i]))
		{
			printf("%s: exit: %s: numeric argument required\n",
				SHELL_NAME, argv[1]);
			i = -2;
			break ;
		}
	}
	if (i != -2 && argc >= 3)
		return (printf("%s: exit: too many arguments\n", SHELL_NAME));
	if (i == -2)
		exit(255);
	exit(ft_atoi(argv[1]));
	return (0);
}
