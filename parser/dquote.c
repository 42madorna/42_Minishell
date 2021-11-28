/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dquote.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madorna- <madorna-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 23:25:46 by madorna-          #+#    #+#             */
/*   Updated: 2021/11/28 05:32:54 by madorna-         ###   ########.fr       */
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
	printf("Called Dquote function\n");
	if (((mini->flag & DQUOTE) == DQUOTE) == 1)
			mini->flag -= DQUOTE;
	else if (((mini->flag & QUOTE) == QUOTE) != 1)
	{
		mini->flag += DQUOTE;
		printf("Dquote!\n");
	}
	/*
	** This is to call DOLLAR function if flag DOLLAR is set
	*/
	if (((mini->flag & DOLLAR) == DOLLAR) == 1)
		mini->p[DOLLAR](mini);
	return (0);
}
