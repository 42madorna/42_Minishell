/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_argv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madorna- <madorna-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 06:35:25 by madorna-          #+#    #+#             */
/*   Updated: 2022/02/08 07:32:59 by madorna-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void
	ft_list_to_argv(t_cmd *cmd)
{
	t_list	*l_argv;
	int		n_argv;

	l_argv = cmd->l_argv;
	n_argv = ft_lstsize(l_argv);
	cmd->argv = calloc(n_argv + 1, sizeof(char*));
	while (l_argv)
	{
		cmd->argv[cmd->argc++] = l_argv->content;
		l_argv = l_argv->next;
	}
}

void
	make_argv(t_mini *mini)
{
	t_list	*cmds;

	cmds = mini->cmds;
	while (cmds)
	{
		ft_list_to_argv(cmds->content);
		cmds = cmds->next;
	}
}
