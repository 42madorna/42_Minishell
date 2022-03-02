/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaliste <agaliste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 17:57:21 by agaliste          #+#    #+#             */
/*   Updated: 2022/03/02 18:00:48 by agaliste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void
	ft_init_pipex(int *in_fd, int pipes[2])
{
	signal(SIGQUIT, signal_q);
	signal(SIGINT, signal_q);
	(*in_fd) = STDIN_FILENO;
	(pipes)[0] = STDIN_FILENO;
	(pipes)[1] = STDOUT_FILENO;
}
