/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madorna- <madorna-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 23:25:46 by madorna-          #+#    #+#             */
/*   Updated: 2022/02/05 03:56:43 by madorna-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Add QUOTE content to buffer except when APPEND, DELIMITER, IN, OUT are
** 	specified, in that case, the normal behaviour of these flags may occur!
*/
int
	parse_quote(t_mini *mini)
{
	if (mini->flag == QUOTE)
	{
		mini->flag -= QUOTE;
		mini->line_cpy++;
	}
	else if (mini->flag != DQUOTE)
	{
		if (((mini->flag & DOLLAR) == DOLLAR) == 1)
			mini->flag -= DOLLAR;
		mini->flag = QUOTE;
		mini->line_cpy++;
	}
	return (0);
}
