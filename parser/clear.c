/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madorna- <madorna-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 23:14:57 by madorna-          #+#    #+#             */
/*   Updated: 2021/12/01 04:20:49 by madorna-         ###   ########.fr       */
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
		if (((((mini->flag & APPEND) == APPEND) == 1)))
			mini->flag -= APPEND;
		if (((((mini->flag & IN) == IN) == 1)))
			mini->flag -= IN;
		if (((((mini->flag & DELIMITER) == DELIMITER) == 1)))
			mini->flag -= DELIMITER;
		if (((((mini->flag & OUT) == OUT) == 1)))
			mini->flag -= OUT;
	}
	mini->flag += CLEAR;
	return (0);
}
