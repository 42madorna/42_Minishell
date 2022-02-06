/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delimiter.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madorna- <madorna-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 23:25:46 by madorna-          #+#    #+#             */
/*   Updated: 2022/02/05 04:03:47 by madorna-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** If no word is after DELIMITER (<<), error.
** Add words to (t_list*)mini->delimiters and not to buffer!
*/
int
	parse_delimiter(t_mini *mini)
{
	if (mini->flag != QUOTE && ((mini->flag & DQUOTE) == DQUOTE) != 1)
	{
		if (((mini->flag & DOLLAR) == DOLLAR) == 1)
			mini->flag -= DOLLAR;
		mini->flag = DELIMITER;
		mini->line_cpy += 2;
	}
	return (0);
}
