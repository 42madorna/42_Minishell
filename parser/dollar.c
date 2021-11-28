/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madorna- <madorna-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 23:25:46 by madorna-          #+#    #+#             */
/*   Updated: 2021/11/28 05:23:22 by madorna-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Parse env_var name after DOLLAR ($) and add the content to buffer.
** If there is a space after dollar, put the dollar into the buffer
*/
int
	parse_dollar(t_mini *mini)
{
	if (((mini->flag & QUOTE) == QUOTE) != 1)
	{
		mini->flag += DOLLAR;
		printf("Dollar!\n");
	}
	printf("Called Dollar function\n");
	// mini->flag -= DOLLAR;
	return (0);
}
