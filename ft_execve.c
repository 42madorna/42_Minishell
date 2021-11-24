/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madorna- <madorna-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 00:25:30 by madorna-          #+#    #+#             */
/*   Updated: 2021/11/24 00:46:49 by madorna-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int
	ft_execve(t_cmd command)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
		execve(command.argv[0], command.argv, command.env);
	else if (pid > 0)
		pid = wait(&status);
	status = WEXITSTATUS(status);
	return (status);
}
