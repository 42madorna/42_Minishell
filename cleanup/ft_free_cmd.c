/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madorna- <madorna-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 04:36:50 by madorna-          #+#    #+#             */
/*   Updated: 2022/02/12 05:16:58 by madorna-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cleanup.h"

void
	ft_free_cmd(void *cmd)
{
	t_cmd *cmd_node;

	cmd_node = cmd;
	if (cmd_node->argv)
		free(cmd_node->argv);
	if (cmd_node->env)
		ft_free_tab(cmd_node->env);
	if (cmd_node->path)
		free(cmd_node->path);
	ft_lstclear(&cmd_node->l_argv, free);
	free(cmd_node->l_argv);
	cmd_node->env = NULL;
	cmd_node->path = NULL;
	cmd_node->l_argv = NULL;
	free(cmd_node);
	cmd_node = NULL;
}
