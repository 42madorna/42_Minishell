/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madorna- <madorna-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 18:14:05 by madorna-          #+#    #+#             */
/*   Updated: 2022/02/11 21:12:05 by madorna-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void
	signal_q(int sig)
{
	int	i;

	i = 0;
	while (g_pid[i])
	{
		kill(g_pid[i], sig);
		g_pid[i++] = 0;
	}
	if (sig == 3)
		printf("Quit: %d\n", sig);
	else
		printf("\n");
}

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

int
	execute(int in, int out, t_cmd *cmd, t_mini *mini)
{
	pid_t	pid;
	int		saved_fd[2];

	pid = fork();
	if (pid == 0)
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
		if (!builtin(mini))
		{
			close_dup(saved_fd);
			return (0);
		}
		if (cmd->notexists)
		{
			ft_putstr_fd(SHELL_NAME, STDERR_FILENO);
			ft_putstr_fd(": ", STDERR_FILENO);
			ft_putstr_fd(cmd->argv[0], STDERR_FILENO);
			if (cmd->notexists == 1)
				ft_putstr_fd(": command not found\n", STDERR_FILENO);
			else
				ft_putstr_fd(": is a directory\n", STDERR_FILENO);
			close_dup(saved_fd);
			cmd->notexists == 1 ? exit (127) : exit(126);
		}
		execve(cmd->path, cmd->argv, cmd->env);
		close_dup(saved_fd);
		return (0);
	}
	builtin_parent(mini);
	return (pid);
}

void
	pipex(t_mini *mini)
{
	int		in_fd;
	int		pipes[2];
	t_cmd	*cmd_node;
	pid_t	pid;

	signal(SIGQUIT, signal_q);
	signal(SIGINT, signal_q);
	in_fd = STDIN_FILENO;
	pipes[0] = STDIN_FILENO;
	pipes[1] = STDOUT_FILENO;
	while (mini->cmds && mini->cmds->next)
	{
		cmd_node = mini->cmds->content;
		if (!cmd_node->argv[0] || !cmd_node->argv[0][0])
		{
			mini->cmds = mini->cmds->next;
			continue ;
		}
		pipe(pipes);
		pid = execute(in_fd, pipes[STDOUT_FILENO], cmd_node, mini);
		wait(&pid);
		mini->ret = WEXITSTATUS(pid);
		close(pipes[STDOUT_FILENO]);
		in_fd = pipes[STDIN_FILENO];
		mini->cmds = mini->cmds->next;
	}
	if (mini->cmds)
	{
		cmd_node = mini->cmds->content;
		if (cmd_node && cmd_node->argv && cmd_node->argv[0])
		{
			if (!ft_strncmp(cmd_node->argv[0], "exit", 5))
				builtin(mini);
			pid = execute(in_fd, pipes[STDOUT_FILENO], cmd_node, mini);
			wait(&pid);
			mini->ret = WEXITSTATUS(pid);
		}
	}
	if (in_fd)
		close(in_fd);
}
