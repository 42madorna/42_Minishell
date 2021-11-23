/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madorna- <madorna-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 00:49:50 by madorna-          #+#    #+#             */
/*   Updated: 2021/11/23 23:49:44 by madorna-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void
	parse(t_mini *mini)
{
	char	*line;

	line = mini->line;
	while (*line)
	{
		if (!strcmp(line, "exit"))
		{
			mini->argv[0] = strdup("exit\0");
			builtin(mini->argv, mini);
		}
		write(1, line, 1);
		++line;
	}
	write(1, "\n", 1);
}

void
	signal_h(int what)
{
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

int
	main(int argc, char **argv, char **env)
{
	t_mini	mini;

	ft_bzero(&mini, sizeof(t_mini));
	mini.argc = argc;
	mini.argv = argv;
	mini.env = env;
	printf("%s\n", getenv("PATH"));
	signal(SIGINT, signal_h);
	signal(SIGHUP, signal_h);
	while (1)
	{
		mini.line = readline(SHELL_NAME "$ ");
		if (mini.line && *mini.line)
		{
			add_history(mini.line);
			parse(&mini);
			free(mini.line);
		}
		else if (!mini.line)
		{
			write(1, "exit\n", 6);
			exit(0);
		}
	}
}
