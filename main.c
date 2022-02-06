/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madorna- <madorna-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 00:49:50 by madorna-          #+#    #+#             */
/*   Updated: 2022/02/06 07:49:53 by madorna-         ###   ########.fr       */
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
	set_functions(t_mini *mini)
{
	mini->p[CLEAR] = parse_clear;
	mini->p[PIPE] = parse_pipe;
	mini->p[OUT] = parse_out;
	mini->p[QUOTE] = parse_quote;
	mini->p[DELIMITER] = parse_delimiter;
	mini->p[IN] = parse_in;
	mini->p[APPEND] = parse_append;
	mini->p[DQUOTE] = parse_dquote;
	mini->p[DOLLAR] = parse_dollar;
}

/*
** Minishell
** Subject 
*/
int
	main(int argc, char **argv, char **env)
{
	t_mini	mini;

	ft_bzero(&mini, sizeof(t_mini));
	mini.argc = argc;
	mini.argv = argv;
	mini.env = env;
	signal(SIGINT, signal_h);
	set_functions(&mini);
	ft_env_to_lst(&mini);
	while (1)
	{
		signal(SIGQUIT, SIG_IGN);
		mini.flag = CLEAR;
		mini.pipe_count = 0;
		promt(&mini, 0);
		if (mini.line && *mini.line)
		{
			add_history(mini.line);
			quote_finder(&mini);
			// if (!parse(&mini))
			// {
				make_argv(&mini);
				make_env(&mini);
				pipex(&mini);
			// }
			mini.cmds = NULL;
			free(mini.line);
		}
		else if (!mini.line)
		{
			printf("exit\n");
			rl_clear_history();
			break ;
		}
	}
	ft_lstclear(&mini.l_env, ft_free_env);
	/*
	** TODO: Leaks!
	*/
	return (0);
}
