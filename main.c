/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madorna- <madorna-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 00:49:50 by madorna-          #+#    #+#             */
/*   Updated: 2022/02/06 20:33:10 by madorna-         ###   ########.fr       */
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

void
	ft_delim(t_mini *mini)
{
	t_list	*l_delim;
	char	*delim;

	l_delim = mini->delimiters;
	while (l_delim)
	{
		if (!ft_strncmp(l_delim->content, mini->line, ft_strlen(mini->line) + 1))
			l_delim = l_delim->next;
		printf("Expecting '%s'\n", l_delim->content);
		promt(mini, 1);
		if (!mini->line || !*mini->line)
		{
			printf("%s: warning: (wanted `%s')\n", SHELL_NAME,
				l_delim->content);
			l_delim = l_delim->next;
			continue ;
		}
		if (!ft_strncmp(l_delim->content, mini->line, ft_strlen(mini->line) + 1))
			l_delim = l_delim->next;
		else
			l_delim = mini->delimiters;
	}
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
			ft_delim(&mini);
			// if (!parse(&mini))
			// {
				make_argv(&mini);
				make_env(&mini);
				pipex(&mini);
			// }
			mini.cmds = NULL;
			mini.delimiters = NULL;
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
	** At this moment:
	** 	· l_argv
	** 	· t_cmd
	** 	· PATH
	** 	· l_env/t_cmd env
	** 	· t_cmd path
	** 	· delimitters
	*/
	return (0);
}
