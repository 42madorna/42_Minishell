/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madorna- <madorna-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 23:25:46 by madorna-          #+#    #+#             */
/*   Updated: 2022/02/05 03:40:41 by madorna-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** If there is no file after IN (<), or file does not exist, error!
** Add last file to cmds->infile and not to buffer.
*/
int
	parse_in(t_mini *mini)
{
	if (((mini->flag & QUOTE) == QUOTE) != 1
		&& ((mini->flag & DQUOTE) == DQUOTE) != 1)
	{
		if (((mini->flag & DOLLAR) == DOLLAR) == 1)
			mini->flag -= DOLLAR;
		mini->flag = IN;
		mini->line_cpy++;
	}
	return (0);
}
