/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madorna- <madorna-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 23:18:31 by madorna-          #+#    #+#             */
/*   Updated: 2021/11/29 05:34:10 by madorna-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** If there isn't command[0], error!
** Add command to new (t_list*)mini->cmds node with t_cmd content
*/
int
	parse_pipe(t_mini *mini)
{
	if (((mini->flag & QUOTE) == QUOTE) != 1
		&& ((mini->flag & DQUOTE) == DQUOTE) != 1)
	{
		mini->flag += PIPE;
		mini->line_cpy++;
	}
	return (0);
}
