/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madorna- <madorna-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 00:49:50 by madorna-          #+#    #+#             */
/*   Updated: 2021/11/28 00:58:18 by madorna-         ###   ########.fr       */
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

	// mini->p[CLEAR](mini);
	// mini->p[PIPE](mini);
	// mini->p[OUT](mini);
	// mini->p[QUOTE](mini);
	// mini->p[DELIMITER](mini);
	// mini->p[IN](mini);
	// mini->p[APPEND](mini);
	// mini->p[DQUOTE](mini);
	// mini->p[DOLLAR](mini);
}

int
	main(int argc, char **argv, char **env)
{
	t_mini	mini;

	ft_bzero(&mini, sizeof(t_mini));
	mini.argc = argc;
	mini.argv = argv;
	mini.env = env;
	signal(SIGINT, signal_h);
	signal(SIGQUIT, signal_h);
	set_functions(&mini);
	// mini.flag = CLEAR;
	// printf("mini.flag %d\n", mini.flag);
	// // Añadir al binario
	// mini.flag += DQUOTE + DOLLAR;
	// printf("mini.flag %d\n", mini.flag);
	// // Saber si algo está dentro del binario
	// printf("mini.flag %d\n", (mini.flag & DQUOTE) == DQUOTE);
	// if (((mini.flag & DQUOTE) == DQUOTE) == 1)
	// 	mini.p[DQUOTE](&mini);
	// if (((mini.flag & DOLLAR) == DOLLAR) == 1)
	// 	mini.p[DOLLAR](&mini);
	// if (mini.flag != 0)
	// 	printf("Parse error\n");
	while (1)
	{
		mini.flag = CLEAR;
		promt(&mini, 0);
		if (mini.line && *mini.line)
		{
			add_history(mini.line);
			parse(&mini);
			free(mini.line);
		}
		else if (!mini.line)
		{
			write(1, "exit\n", 6);
			rl_clear_history();
			break ;
		}
	}
	return (0);
}
