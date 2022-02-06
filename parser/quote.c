/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madorna- <madorna-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 23:25:46 by madorna-          #+#    #+#             */
/*   Updated: 2022/02/06 00:29:08 by madorna-         ###   ########.fr       */
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
		// mini->line_cpy++;
	}
	else if (mini->flag != DQUOTE)
	{
		mini->flag = QUOTE;
		// mini->line_cpy++;
	}
	return (0);
}
