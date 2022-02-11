/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madorna- <madorna-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 23:25:46 by madorna-          #+#    #+#             */
/*   Updated: 2022/02/11 19:12:03 by madorna-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** If there is no file after APPEND (>>), or file does not exist, error!
** Add last file to cmds->outfile and not to buffer.
** All the files have to be created it these don't exist!
*/
int
	parse_append(t_mini *mini)
{
	if (mini->flag != QUOTE && ((mini->flag & DQUOTE) == DQUOTE) != 1)
	{
		if (((mini->flag & DOLLAR) == DOLLAR) == 1)
			mini->flag -= DOLLAR;
		mini->flag = APPEND;
		mini->line_cpy += 2;
	}
	return (0);
}
