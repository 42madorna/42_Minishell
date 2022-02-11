/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madorna- <madorna-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 23:18:31 by madorna-          #+#    #+#             */
/*   Updated: 2022/02/11 19:34:50 by madorna-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** If there isn't command[0], error!
** Add command to new (t_list*)mini->cmds node with t_cmd content
*/
/*
** TODO: Fix Pipe
*/
int
	parse_pipe(t_mini *mini)
{
	if (mini->flag != QUOTE && mini->flag != DQUOTE)
	{
		if (((mini->flag & DOLLAR) == DOLLAR) == 1)
			mini->flag -= DOLLAR;
		mini->flag = PIPE;
		mini->pipe_count++;
	}
	return (0);
}
