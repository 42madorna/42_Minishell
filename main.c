/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madorna- <madorna-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 00:49:50 by madorna-          #+#    #+#             */
/*   Updated: 2022/02/13 03:45:13 by madorna-         ###   ########.fr       */
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
	t_list	*begin_node;

	l_delim = mini->delimiters;
	begin_node = l_delim;
	while (l_delim)
	{
		if (mini->line && *mini->line && !ft_strncmp(l_delim->content,
				mini->line, ft_strlen(mini->line) + 1))
			l_delim = l_delim->next;
		promt(mini, 1);
		if (mini->line)
		{
			if (!ft_strncmp(l_delim->content, mini->line,
				ft_strlen(mini->line) + 1))
				l_delim = l_delim->next;
			else
				l_delim = begin_node;
			continue ;
		}
		printf("%s: warning: unexpected '\\0' (wanted `%s')\n", SHELL_NAME,
			(char *)l_delim->content);
		l_delim = l_delim->next;
		begin_node = l_delim;
	}
}

void
	ft_check_command(t_mini *mini)
{
	t_list	*cmds;
	t_cmd	*cmd_node;

	cmds = mini->cmds;
	while (cmds)
	{
		cmd_node = cmds->content;
		cmd_node->notexists = 0;
		if (!cmd_node->outfile)
			cmd_node->outfile = 1;
		cmd_node->notexists = ft_search_cmd(mini->l_env, cmd_node);
		cmds = cmds->next;
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
	set_functions(&mini);
	ft_env_to_lst(&mini);
	while (1)
	{
		signal(SIGINT, signal_h);
		signal(SIGQUIT, SIG_IGN);
		mini.flag = CLEAR;
		mini.parse_err = 0;
		promt(&mini, 0);
		if (mini.line && *mini.line)
		{
			add_history(mini.line);
			quote_finder(&mini);
			if (!mini.parse_err)
			{
				ft_delim(&mini);
				make_argv(&mini);
				make_env(&mini);
				ft_check_command(&mini);
				pipex(&mini);
			}
			mini.cmds = NULL;
			if (mini.env_cmd)
				ft_free_tab(mini.env_cmd);
			ft_lstclear(&mini.delimiters, free);
			mini.chars = NULL;
			free(mini.line);
			mini.line = NULL;
		}
		else if (!mini.line)
		{
			rl_clear_history();
			printf("exit\n");
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
	** 	· delimiters
	*/
	return (0);
}
