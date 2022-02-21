/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madorna- <madorna-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 04:16:57 by madorna-          #+#    #+#             */
/*   Updated: 2022/02/21 09:40:07 by madorna-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void
	mini_loop(t_mini *mini)
{
	add_history(mini->line);
	quote_finder(mini);
	if (!mini->parse_err)
	{
		ft_delim(mini);
		make_argv(mini);
		make_env(mini);
		ft_check_command(mini);
		pipex(mini);
	}
	mini->cmds = NULL;
	if (mini->env_cmd)
		ft_free_tab(mini->env_cmd);
	ft_lstclear(&mini->delimiters, free);
	mini->chars = NULL;
	free(mini->line);
	mini->line = NULL;
	mini->env_cmd = NULL;
}
