/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madorna- <madorna-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 18:14:05 by madorna-          #+#    #+#             */
/*   Updated: 2022/03/02 11:40:56 by madorna-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Pipex (minishell edition)
** How should this work?
** Pipex receives as parameter t_mini *mini, which contains
** 	t_list *cmds of t_cmd.
** t_cmd has the following fields:
** 	· int argc (argument count for the command)
** 	· char **argv (command arguments)
** 	· char **env (command environment variables)
** 	· int infile (the in fd. Defaults to STDIN_FILENO)
** 	· int outfile (the out fd. Defaults to STDOUT_FILENO)
** 	· char *path (the path of the command to execute)
** 	· pit_t pid (the PID of the command once executed, will be set in ft_execve)
** Pipex should handle the t_list *cmds of t_cmd and execute the commands in
** 	order. Pipex can receive 1 to n commands separated as nodes of the t_list
** 	list.
*/
/*
** Right now the code below is an approach to the "expected behabiour" of pipex,
** 	but doesn't control any of fd. This has to be handled with the "pipex style"
** 	(obviously changed to work in minishell), the code may be kinda similar to
** 	pipex in bonus version.
** URL to PIPEX subject:
** 	https://cdn.intra.42.fr/pdf/pdf/38119/en.subject.pdf
*/

void
	close_dup(int saved_fd[2])
{
	dup2(saved_fd[0], STDIN_FILENO);
	dup2(saved_fd[1], STDOUT_FILENO);
	if (saved_fd[0] != STDIN_FILENO)
		close(saved_fd[0]);
	if (saved_fd[STDOUT_FILENO] != STDOUT_FILENO)
		close(saved_fd[1]);
}

void
	ft_in_out(int in, int out, int saved_fd[2], t_cmd *cmd)
{
	if (in != STDIN_FILENO)
	{
		dup2(in, STDIN_FILENO);
		close(in);
	}
	if (out != STDOUT_FILENO)
	{
		dup2(out, STDOUT_FILENO);
		close(out);
	}
	dup2(STDIN_FILENO, saved_fd[0]);
	dup2(STDOUT_FILENO, saved_fd[1]);
	dup2(cmd->infile, STDIN_FILENO);
	dup2(cmd->outfile, STDOUT_FILENO);
}

int
	execute(int in, int out, t_cmd *cmd, t_mini *mini)
{
	pid_t	pid;
	int		saved_fd[2];

	if (!cmd->argv || !cmd->argv[0] || !cmd->argv[0][0])
		return (0);
	pid = fork();
	if (pid == 0)
	{
		ft_in_out(in, out, saved_fd, cmd);
		if (!builtin(mini))
		{
			close_dup(saved_fd);
			return (0);
		}
		ft_check_existence(cmd, saved_fd);
		execve(cmd->path, cmd->argv, cmd->env);
		close_dup(saved_fd);
		return (0);
	}
	builtin_parent(mini);
	return (pid);
}

void
	ft_init_pipex(int *in_fd, int pipes[2])
{
	signal(SIGQUIT, signal_q);
	signal(SIGINT, signal_q);
	(*in_fd) = STDIN_FILENO;
	(pipes)[0] = STDIN_FILENO;
	(pipes)[1] = STDOUT_FILENO;
}

void
	pipex(t_mini *mini)
{
	int		in_fd;
	int		pipes[2];
	t_cmd	*cmd_node;
	t_list	*cmds;

	ft_init_pipex(&in_fd, pipes);
	cmds = mini->cmds;
	while (mini->cmds)
	{
		cmd_node = mini->cmds->content;
		if (mini->cmds->next)
			pipe(pipes);
		else if (!ft_strncmp(cmd_node->argv[0], "exit", 5))
			builtin(mini);
		g_pid[cmd_node->num] = execute(in_fd,
				pipes[STDOUT_FILENO], cmd_node, mini);
		wait(&g_pid[cmd_node->num]);
		mini->ret = WEXITSTATUS(g_pid[cmd_node->num]);
		if (mini->cmds->next)
			close(pipes[STDOUT_FILENO]);
		in_fd = pipes[STDIN_FILENO];
		mini->cmds = mini->cmds->next;
	}
	if (in_fd)
		close(in_fd);
	ft_lstclear(&cmds, ft_free_cmd);
}
