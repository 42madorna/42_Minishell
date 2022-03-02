/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madorna- <madorna-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 16:52:20 by madorna-          #+#    #+#             */
/*   Updated: 2022/03/02 11:41:26 by madorna-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int
	builtin(t_mini *mini)
{
	t_cmd	*cmd;

	cmd = mini->cmds->content;
	if (!ft_strncmp(cmd->argv[0], "exit", 5))
		ft_exit(cmd->argc, cmd->argv, mini->l_env);
	if (!ft_strncmp(cmd->argv[0], "pwd", 4))
		exit(ft_pwd(cmd->argc, cmd->argv, mini->l_env));
	if (!ft_strncmp(cmd->argv[0], "cd", 3))
		exit(0);
	if (!ft_strncmp(cmd->argv[0], "echo", 5))
		exit(ft_echo(cmd->argc, cmd->argv, mini->l_env));
	if (!ft_strncmp(cmd->argv[0], "env", 4))
		exit(ft_env(cmd->argc, cmd->argv, mini->l_env));
	if (!ft_strncmp(cmd->argv[0], "unset", 6))
		exit(0);
	if (!ft_strncmp(cmd->argv[0], "export", 7))
		exit(ft_export(cmd->argc, cmd->argv, mini->l_env));
	if (!ft_strncmp(cmd->argv[0], "dsbksdgbksdghsh", 16))
		ft_dsbksdgbksdghsh();
	return (1);
}

int
	builtin_parent(t_mini *mini)
{
	t_cmd	*cmd;

	cmd = mini->cmds->content;
	if (!ft_strncmp(cmd->argv[0], "cd", 3))
		return (ft_cd(cmd->argc, cmd->argv, mini->l_env));
	if (!ft_strncmp(cmd->argv[0], "export", 7))
		return (ft_export_noprint(cmd->argc, cmd->argv, mini->l_env));
	if (!ft_strncmp(cmd->argv[0], "unset", 6))
		return (ft_unset(cmd->argc, cmd->argv, &mini->l_env));
	return (1);
}
