/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madorna- <madorna-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 23:14:57 by madorna-          #+#    #+#             */
/*   Updated: 2021/11/29 05:49:39 by madorna-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Normal text, no flags. Put in buffer normally
*/
int
	parse_clear(t_mini *mini)
{
	if (*mini->line_cpy == ' ' && (((mini->flag & DOLLAR) == DOLLAR) == 1))
		mini->flag -= DOLLAR;
	mini->flag += CLEAR;
	// printf("Called Clear function\n");
	return (0);
}
