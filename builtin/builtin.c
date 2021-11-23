/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madorna- <madorna-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 16:52:20 by madorna-          #+#    #+#             */
/*   Updated: 2021/08/01 00:30:39 by madorna-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int
	builtin(char **argv, t_minishell *mini)
{
	int		argc;

	argc = 0;
	while (argv[argc])
		++argc;
	if (!ft_strcmp(argv[0], "exit"))
		return (ft_exit(argc, argv, mini->env_list, mini));
	if (!ft_strcmp(argv[0], "pwd"))
		return (ft_pwd(argc, argv, mini->env_list));
	if (!ft_strcmp(argv[0], "cd"))
		return (ft_cd(argc, argv, mini->env_list));
	if (!ft_strcmp(argv[0], "echo"))
		return (ft_echo(argc, argv));
	if (!ft_strcmp(argv[0], "env"))
		return (ft_env(argc, argv, mini->env_list));
	if (!ft_strcmp(argv[0], "unset"))
		return (ft_unset(argc, argv, mini->env_list));
	if (!ft_strcmp(argv[0], "export"))
		return (ft_export(argc, argv, mini->env_list));
	return (1);
}
