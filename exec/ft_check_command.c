/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madorna- <madorna-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 04:23:46 by madorna-          #+#    #+#             */
/*   Updated: 2022/02/16 07:27:27 by madorna-         ###   ########.fr       */
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

void
	ft_check_existence(t_cmd *cmd, int saved_fd[2])
{
	if (cmd->notexists)
	{
		ft_putstr_fd(SHELL_NAME, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd(cmd->argv[0], STDERR_FILENO);
		if (cmd->notexists == 1)
			ft_putstr_fd(": command not found\n", STDERR_FILENO);
		else
			ft_putstr_fd(": is a directory\n", STDERR_FILENO);
		close_dup(saved_fd);
		if (cmd->notexists == 1)
			exit(127);
		else
			exit(126);
	}
}
