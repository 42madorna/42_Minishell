/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madorna- <madorna-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 16:52:20 by madorna-          #+#    #+#             */
/*   Updated: 2022/02/09 19:55:20 by madorna-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "libft/libft.h"

static void
	close_dup(int saved_fd[2])
{
	dup2(saved_fd[0], STDIN_FILENO);
	dup2(saved_fd[1], STDOUT_FILENO);
	close(saved_fd[0]);
	close(saved_fd[1]);
}

int
	builtin(char **argv, struct s_mini *mini, int in, int *out)
{
	t_cmd	*cmd;
	int		saved_fd[2];

	cmd = mini->cmds->content;
	if (!ft_strncmp(cmd->argv[0], "exit", 5))
		ft_exit(cmd->argc, cmd->argv, mini->l_env, mini);
	if (!ft_strncmp(cmd->argv[0], "pwd", 4))
		exit(ft_pwd(cmd->argc, cmd->argv, mini->l_env));
	if (!ft_strncmp(cmd->argv[0], "cd", 3))
		exit(ft_cd(cmd->argc, cmd->argv, mini->l_env));
	if (!ft_strncmp(cmd->argv[0], "echo", 5))
		exit(ft_echo(cmd->argc, cmd->argv, mini->l_env));
	if (!ft_strncmp(cmd->argv[0], "env", 4))
		exit(ft_env(cmd->argc, cmd->argv, mini->l_env));
	if (!ft_strncmp(cmd->argv[0], "unset", 6))
		exit(ft_unset(cmd->argc, cmd->argv, &mini->l_env));
	if (!ft_strncmp(cmd->argv[0], "export", 7))
		exit(ft_export(cmd->argc, cmd->argv, mini->l_env));
	if (!ft_strncmp(cmd->argv[0], "dsbksdgbksdghsh", 16))
		ft_dsbksdgbksdghsh();
	return (1);
}
