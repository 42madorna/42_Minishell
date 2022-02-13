/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madorna- <madorna-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 22:11:24 by madorna-          #+#    #+#             */
/*   Updated: 2022/02/14 00:30:11 by madorna-         ###   ########.fr       */
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
	ft_print(t_list *l_env, int argc, char **argv)
{
	int	i;
	int	option;

	option = 0;
	if (!ft_strncmp(argv[i], "-n", ft_strlen(argv[i])))
	{
		option = 1;
		++i;
	}
	while (i < argc)
	{
		if (!ft_strncmp(argv[i], "~", ft_strlen(argv[i]) + 1))
		{
			if (ft_env_value(l_env, "HOME"))
				printf("%s", ft_env_value(l_env, "HOME"));
		}
		else
			printf("%s", argv[i]);
		++i;
		if (argv[i])
			printf(" ");
	}
	return (option);
}

int
	ft_echo(int argc, char **argv, t_list *l_env)
{
	int	i;
	int	option;

	i = 1;
	if (argc < 2)
		return (write(1, "\n", 1) - 1);
	option = ft_print(l_env, argc, argv);
	if (!option)
		printf("\n");
	return (0);
}
