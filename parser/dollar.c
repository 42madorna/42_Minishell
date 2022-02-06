/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madorna- <madorna-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 23:25:46 by madorna-          #+#    #+#             */
/*   Updated: 2022/02/05 17:48:46 by madorna-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Parse env_var name after DOLLAR ($) and add the content to buffer.
** If there is a space or any other special char or even '\0' after dollar,
** 	put the dollar into the buffer.
*/
/*
** TODO: Check DOLLAR flag
*/
int
	parse_dollar(t_mini *mini)
{
	if (mini->flag != QUOTE)
	{
		if (*(mini->line_cpy + 1) == '\0' || *(mini->line_cpy + 1) == '>'
			|| *(mini->line_cpy + 1) == '<' || *(mini->line_cpy + 1) == ' '
			|| *(mini->line_cpy + 1) == '|')
			return (0);
		if (*(mini->line_cpy + 1) != '\'' && *(mini->line_cpy + 1) != '"')
		{
			mini->flag += DOLLAR;
			mini->line_cpy++;
		}
	}
	return (0);
}
