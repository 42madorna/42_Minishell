/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madorna- <madorna-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 22:11:24 by madorna-          #+#    #+#             */
/*   Updated: 2021/12/01 02:55:36 by madorna-         ###   ########.fr       */
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
	if (argc < 2)
		return (write(1, "\n", 1) - 1);
	if (!ft_strncmp(argv[i], "-n", ft_strlen(argv[i])))
	{
		option = 1;
		++i;
	}
	while (i < argc)
	{
		printf("%s", argv[i]);
		++i;
		if (argv[i])
			printf(" ");
	}
	if (!option)
		printf("\n");
	return (0);
}
