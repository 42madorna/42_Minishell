/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madorna- <madorna-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 00:25:30 by madorna-          #+#    #+#             */
/*   Updated: 2022/02/07 01:46:08 by madorna-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int
	ft_execve(t_cmd *cmd)
{
	int					status;

	g_pid[cmd->num] = fork();
	if (g_pid[cmd->num] == 0)
	{
		if (execve(cmd->path, cmd->argv, cmd->env) != 0)
			perror(strerror(errno));
	}
	else if (g_pid[cmd->num] > 0)
		g_pid[cmd->num] = wait(&status);
	status = WEXITSTATUS(status);
	return (status);
}
