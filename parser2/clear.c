/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madorna- <madorna-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 23:14:57 by madorna-          #+#    #+#             */
/*   Updated: 2022/02/05 17:45:46 by madorna-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Normal text, no flags. Put in buffer normally
*/
int
	parse_clear(t_mini *mini)
{
	if (*mini->line_cpy == ' ')
	{
		if ((((mini->flag & DOLLAR) == DOLLAR) == 1))
			mini->flag -= DOLLAR;
		if (mini->flag == APPEND)
			mini->flag -= APPEND;
		if (mini->flag == IN)
			mini->flag -= IN;
		if (mini->flag == DELIMITER)
			mini->flag -= DELIMITER;
		if (mini->flag == OUT)
			mini->flag -= OUT;
	}
	mini->flag += CLEAR;
	return (0);
}
