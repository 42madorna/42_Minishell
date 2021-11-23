/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madorna- <madorna-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 16:52:20 by madorna-          #+#    #+#             */
/*   Updated: 2021/11/23 19:08:39 by madorna-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "libft/libft.h"

int
	builtin(char **argv, struct s_mini *mini)
{
	int		argc;

	argc = 0;
	while (argv[argc])
		++argc;
	if (!ft_strncmp(argv[0], "exit", ft_strlen(argv[0])))
		return (ft_exit(argc, argv, mini->l_env, mini));
	// if (!ft_strcmp(argv[0], "pwd"))
	// 	return (ft_pwd(argc, argv, mini->l_env));
	// if (!ft_strcmp(argv[0], "cd"))
	// 	return (ft_cd(argc, argv, mini->l_env));
	// if (!ft_strcmp(argv[0], "echo"))
	// 	return (ft_echo(argc, argv));
	// if (!ft_strcmp(argv[0], "env"))
	// 	return (ft_env(argc, argv, mini->l_env));
	// if (!ft_strcmp(argv[0], "unset"))
	// 	return (ft_unset(argc, argv, mini->l_env));
	// if (!ft_strcmp(argv[0], "export"))
	// 	return (ft_export(argc, argv, mini->l_env));
	return (1);
}
