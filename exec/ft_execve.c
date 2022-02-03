/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madorna- <madorna-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 00:25:30 by madorna-          #+#    #+#             */
/*   Updated: 2022/02/03 23:51:30 by madorna-         ###   ########.fr       */
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

	// command.argv = malloc(sizeof(char*) * 3);
	// command.argv[0] = "/usr/bin/man";
	// command.argv[1] = "man";
	// command.argv[2] = NULL;
	// TODO: search in the PATH env variable for a match
	/*
	** if (!command)
	** 	return (printf(command not found...))
	*/
	// printf("command path %s\n",command.path);
	// FIXME: [MINS-79] Fix WARNING: terminal is not fully functional (for example in man)
	#ifdef __linux__
		sig.sa_handler = signal_q;
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
