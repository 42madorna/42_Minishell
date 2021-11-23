/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madorna- <madorna-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 22:11:24 by madorna-          #+#    #+#             */
/*   Updated: 2021/08/01 00:28:06 by madorna-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** builtin: echo
** echo writes all the arguments except the option in the first place
** 	(subject says you only have to do option "-n") and if the "-n" option is
** 	supplied, then echo does not print '\n'
*/

int
	ft_echo(int argc, char **argv)
{
	int	i;
	int	option;

	i = 1;
	option = 0;
	write(1, "\n", 1);
	if (argc < 2)
		return (write(1, "\n", 1) - 1);
	if (!ft_strcmp(argv[i], "-n"))
	{
		option = 1;
		++i;
	}
	while (i < argc)
	{
		ft_putstr_fd(argv[i], 1);
		++i;
		if (argv[i])
			write(1, " ", 1);
	}
	if (!option)
		write(1, "\n", 1);
	return (0);
}
