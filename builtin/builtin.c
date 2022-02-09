/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madorna- <madorna-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 16:52:20 by madorna-          #+#    #+#             */
/*   Updated: 2022/02/09 06:20:01 by madorna-         ###   ########.fr       */
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
	{
		dup2(STDIN_FILENO, saved_fd[0]);
		dup2(STDOUT_FILENO, saved_fd[1]);
		if (cmd->outfile != STDOUT_FILENO)
			dup2(cmd->outfile, STDOUT_FILENO);
		else
			dup2(*out, STDOUT_FILENO);
		if (cmd->infile != STDIN_FILENO)
			dup2(cmd->infile, STDIN_FILENO);
		else
			dup2(in, STDIN_FILENO);
		ft_exit(cmd->argc, cmd->argv, mini->l_env, mini);
		close_dup(saved_fd);
		return (0);
	}
	if (!ft_strncmp(cmd->argv[0], "pwd", 4))
	{
		if (in != STDIN_FILENO)
		{
			dup2(in, STDIN_FILENO);
			// close(in);
		}
		if (*out != STDOUT_FILENO)
		{
			dup2(*out, STDOUT_FILENO);
			saved_fd[1] = *out;
			// close(*out);
		}
		// dup2(STDIN_FILENO, saved_fd[0]);
		// dup2(STDOUT_FILENO, saved_fd[1]);
		if (cmd->outfile != STDOUT_FILENO)
			dup2(cmd->outfile, STDOUT_FILENO);
		else
			dup2(*out, STDOUT_FILENO);
		if (cmd->infile != STDIN_FILENO)
			dup2(cmd->infile, STDIN_FILENO);
		else
			dup2(in, STDIN_FILENO);
		ft_pwd(cmd->argc, cmd->argv, mini->l_env);
		*out = saved_fd[1];
		// close_dup(saved_fd);
		return (0);
	}
	if (!ft_strncmp(cmd->argv[0], "cd", 3))
	{
		dup2(STDIN_FILENO, saved_fd[0]);
		dup2(STDOUT_FILENO, saved_fd[1]);
		if (cmd->outfile != STDOUT_FILENO)
			dup2(cmd->outfile, STDOUT_FILENO);
		else
			dup2(*out, STDOUT_FILENO);
		if (cmd->infile != STDIN_FILENO)
			dup2(cmd->infile, STDIN_FILENO);
		else
			dup2(in, STDIN_FILENO);
		(ft_cd(cmd->argc, cmd->argv, mini->l_env));
		return (0);
	}
	if (!ft_strncmp(cmd->argv[0], "echo", 5))
		return (ft_echo(cmd->argc, cmd->argv, mini->l_env));
	if (!ft_strncmp(cmd->argv[0], "env", 4))
		return (ft_env(cmd->argc, cmd->argv, mini->l_env));
	if (!ft_strncmp(cmd->argv[0], "unset", 6))
		return (ft_unset(cmd->argc, cmd->argv, &mini->l_env));
	if (!ft_strncmp(cmd->argv[0], "export", 7))
		return (ft_export(cmd->argc, cmd->argv, mini->l_env));
	if (!ft_strncmp(cmd->argv[0], "dsbksdgbksdghsh", 16))
		return (ft_dsbksdgbksdghsh());
	return (1);
}
