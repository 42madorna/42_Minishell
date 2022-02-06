/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madorna- <madorna-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 00:25:30 by madorna-          #+#    #+#             */
/*   Updated: 2022/02/06 22:36:20 by madorna-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void
	signal_q()
{
	printf("Quit: 3\n");
}

int
	ft_execve(t_cmd *command)
{
	int					status;
	struct sigaction	sig;
	/*
	** FIXME: [MINS-97] ^\ not working as intended
	*/
	#ifdef __linux__
		sig.sa_handler = SIG_DFL;
	#else
		sig.__sigaction_u.__sa_handler = signal_q;
	#endif
	sigaction(SIGQUIT, &sig, NULL);
	command->pid = fork();
	if (command->pid == 0)
	{
		if (execve(command->path, command->argv, command->env) != 0)
			perror(strerror(errno));
	}
	else if (command->pid > 0)
		command->pid = wait(&status);
	status = WEXITSTATUS(status);
	return (status);
}
