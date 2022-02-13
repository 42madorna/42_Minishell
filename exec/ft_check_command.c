/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madorna- <madorna-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 04:23:46 by madorna-          #+#    #+#             */
/*   Updated: 2022/02/13 04:24:00 by madorna-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
