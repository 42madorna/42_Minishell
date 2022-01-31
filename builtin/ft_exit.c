/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adorna_r <adorna_r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 16:50:18 by madorna-          #+#    #+#             */
/*   Updated: 2022/01/31 00:41:48 by adorna_r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** builtin: exit
** exit writes always "\nexit\n" and then checks:
** 	1. Numeric first argument
** 	2. Arguments can not be >= 3
** If there is not a numeric argument, then calls exit(255), if the argument
** 	is valid, it calls exit using ft_atoi. If no arguments are supplied, then,
** 	exit(0) is called.
** Keep in mind that exit is not meant to take options as the subject says !
*/

int
	ft_exit(int argc, char **argv, t_list *env, t_mini *mini)
{
	int		i;

	(void)env;
	i = -1;
	ft_putstr_fd("exit\n", 1);
	if (argc == 1)
		exit(0);
	while (argv[1][++i])
	{
		if (ft_isalpha(argv[1][i]))
		{
			// FIXME: ? numeric argument on exit
			ft_putstr_fd("minishell: exit: ", 1);
			ft_putstr_fd(argv[1], 1);
			ft_putstr_fd(": numeric argument required\n", 1);
			i = -2;
			break ;
		}
	}
	if (i != -2 && argc >= 3)
		return (write(1, "minishell: exit: too many arguments\n", 36));
	if (i == -2)
		exit(255);
	exit(ft_atoi(argv[1]));
	return (0);
}
