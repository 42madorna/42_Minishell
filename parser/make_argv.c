/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_argv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madorna- <madorna-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 06:35:25 by madorna-          #+#    #+#             */
/*   Updated: 2021/11/30 20:27:46 by madorna-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void
	noname(t_cmd *cmd)
{
	t_list	*l_argv;
	int		n_argv;
	int		i;

	l_argv = cmd->l_argv;
	n_argv = ft_lstsize(l_argv);
	cmd->argv = calloc(n_argv, sizeof(char*));
	i = 0;
	while (l_argv)
	{
		cmd->argv[i] = l_argv->content;
		l_argv = l_argv->next;
		i++;
	}
}

void
	make_argv(t_mini *mini)
{
	t_list	*cmds;
	t_cmd	*cmd;

	cmds = mini->cmds;
	while (cmds)
	{
		// cmd = cmds->content;
		noname(cmds->content);
		cmds = cmds->next;
	}
}
