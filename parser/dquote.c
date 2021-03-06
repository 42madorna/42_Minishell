/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dquote.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madorna- <madorna-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 23:25:46 by madorna-          #+#    #+#             */
/*   Updated: 2022/02/11 19:35:04 by madorna-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Add DQUOTE content to buffer except when APPEND, DELIMITER, IN, OUT are
** 	specified, in that case, the normal behaviour of these flags may occur!
** If there is a $ inside DQUOTE, parse it with mini->p[DOLLAR](t_mini*)
*/
int
	parse_dquote(t_mini *mini)
{
	if (mini->flag == DQUOTE)
		mini->flag -= DQUOTE;
	else if (mini->flag != QUOTE)
		mini->flag = DQUOTE;
	return (0);
}
