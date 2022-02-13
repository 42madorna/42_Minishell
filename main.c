/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madorna- <madorna-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 00:49:50 by madorna-          #+#    #+#             */
/*   Updated: 2022/02/13 05:33:32 by madorna-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void
	signal_h(int signal)
{
	if (signal == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void
	promt(t_mini *mini, int type)
{
	static char	*names[] = {SHELL_NAME"$ ", "> "};

	mini->line = readline(names[type]);
}

void
	ft_strc_init(t_mini *mini)
{
	set_functions(mini);
	ft_env_to_lst(mini);
}

/*
** Minishell
** Subject https://cdn.intra.42.fr/pdf/pdf/34911/en.subject.pdf
*/
/*
** TODO: [MINS-111] Leaks!
** At this moment:
** 	· l_argv
** 	· t_cmd
** 	· PATH
** 	· l_env/t_cmd env
** 	· t_cmd path
** 	· delimiters
*/
int
	main(int argc, char **argv, char **env)
{
	t_mini	mini;

	ft_bzero(&mini, sizeof(t_mini));
	mini.argc = argc;
	mini.argv = argv;
	mini.env = env;
	ft_strc_init(&mini);
	while (1)
	{
		signal(SIGINT, signal_h);
		signal(SIGQUIT, SIG_IGN);
		mini.flag = CLEAR;
		mini.parse_err = 0;
		promt(&mini, 0);
		if (mini.line && *mini.line)
			mini_loop(&mini);
		else if (!mini.line)
		{
			printf("exit\n");
			rl_clear_history();
			break ;
		}
	}
	ft_lstclear(&mini.l_env, ft_free_env);
	return (0);
}
