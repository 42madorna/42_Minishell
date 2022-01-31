/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madorna- <madorna-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 00:49:50 by madorna-          #+#    #+#             */
/*   Updated: 2022/01/31 17:53:33 by madorna-         ###   ########.fr       */
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
	if (signal == SIGQUIT)
		printf("SIGQUIT RECEIVED; MUST HANDLE IT\n");
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
	ft_env_to_lst(&mini);
	while (1)
	{
		mini.flag = CLEAR;
		promt(&mini, 0);
		if (mini.line && *mini.line)
		{
			add_history(mini.line);
			if (!parse(&mini))
			{
				make_argv(&mini);
				// TODO: Pipex. (This code is temporary; pipex should call
				// 	ft_search_cmd then ft_execve)
				while (mini.cmds)
				{
					// ((t_cmd*)(mini.cmds->content))->env = env; // FIXME: MINS-79
					if (!((t_cmd*)(mini.cmds->content))->argv[0][0])
						break ;
					if (builtin(argv, &mini))
					{
						if (ft_search_cmd(mini.l_env, (t_cmd*)(mini.cmds->content))) // TODO: Check if this works OK
						{
							printf("%s: %s: command not found\n", SHELL_NAME,
								((t_cmd*)(mini.cmds->content))->argv[0]);
							break ;
						}
						else
							mini.ret = ft_execve(*(t_cmd*)(mini.cmds->content));
					}
					mini.cmds = mini.cmds->next;
				}
				// TODO: If not found, builtins! // WARNING: This may be considered as cheating
			}
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
	/*
	** TODO: Leaks!
	*/
	return (0);
}
