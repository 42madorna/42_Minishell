/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madorna- <madorna-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 18:14:05 by madorna-          #+#    #+#             */
/*   Updated: 2022/02/03 19:01:02 by madorna-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** TODO: [MINS-59] (PIPEX)
*/
void
	pipex(t_mini *mini)
{
	while (mini->cmds)
	{
		// ((t_cmd*)(mini->cmds->content))->env = env; // FIXME: MINS-79
		if (!((t_cmd*)(mini->cmds->content))->argv[0][0])
			break ;
		if (builtin(((t_cmd*)(mini->cmds->content))->argv, mini))
		{
			if (ft_search_cmd(mini->l_env, (t_cmd*)(mini->cmds->content))) // TODO: Check if this works OK
			{
				printf("%s: %s: command not found\n", SHELL_NAME,
					((t_cmd*)(mini->cmds->content))->argv[0]);
				break ;
			}
			else
				mini->ret = ft_execve(*(t_cmd*)(mini->cmds->content));
			// TODO: Leaks
		}
		mini->cmds = mini->cmds->next;
	}
}