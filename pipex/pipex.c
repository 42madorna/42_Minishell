/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madorna- <madorna-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 18:14:05 by madorna-          #+#    #+#             */
/*   Updated: 2022/02/07 20:10:45 by madorna-         ###   ########.fr       */
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
** TODO: [MINS-59] (PIPEX)
*/
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
	pipex(t_mini *mini)
{
	int saved_stdout;
	int saved_stdin;
	int	status;
	int	pipes[2];

	signal(SIGQUIT, signal_q);
	signal(SIGINT, signal_q);
	while (mini->cmds)
	{
		if (!((t_cmd*)(mini->cmds->content))->argv[0] || !((t_cmd*)(mini->cmds->content))->argv[0][0])
			break ;
		saved_stdout = dup(STDOUT_FILENO);
		saved_stdin = dup(STDIN_FILENO);
		dup2(((t_cmd*)(mini->cmds->content))->infile, STDIN_FILENO);
		pipe(pipes);
		g_pid[((t_cmd *)(mini->cmds->content))->num] = fork();
		if (g_pid[((t_cmd *)(mini->cmds->content))->num] == 0)
		{
			close(pipes[READ_END]);
			dup2(((t_cmd*)(mini->cmds->content))->outfile, STDOUT_FILENO);
			if (builtin(((t_cmd*)(mini->cmds->content))->argv, mini))
			{
				if (ft_search_cmd(mini->l_env, (t_cmd*)(mini->cmds->content))) // TODO: Check if this works OK
				{
					printf("%s: %s: command not found\n", SHELL_NAME,
						((t_cmd*)(mini->cmds->content))->argv[0]);
					break ;
				}
				else
				{
					mini->ret = ft_execve((t_cmd*)(mini->cmds->content));
				}
			}
			mini->ret = 0;
		}
		else if (g_pid[((t_cmd *)(mini->cmds->content))->num] > 0)
			g_pid[((t_cmd *)(mini->cmds->content))->num] = wait(&status);
		status = WEXITSTATUS(status);
		// kill(g_pid[((t_cmd *)(mini->cmds->content))->num], SIGINT);
		// if (builtin(((t_cmd*)(mini->cmds->content))->argv, mini))
		// {
		// 	if (ft_search_cmd(mini->l_env, (t_cmd*)(mini->cmds->content))) // TODO: Check if this works OK
		// 	{
		// 		printf("%s: %s: command not found\n", SHELL_NAME,
		// 			((t_cmd*)(mini->cmds->content))->argv[0]);
		// 		break ;
		// 	}
		// 	else
		// 	{
		// 		mini->ret = ft_execve((t_cmd*)(mini->cmds->content));
		// 	}
		// }
		dup2(saved_stdout, STDOUT_FILENO);
		dup2(saved_stdin, STDIN_FILENO);
		close(saved_stdout);
		close(saved_stdin);
		mini->cmds = mini->cmds->next;
	}
}