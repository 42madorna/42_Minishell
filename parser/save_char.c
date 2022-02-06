/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_char.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madorna- <madorna-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 02:50:48 by madorna-          #+#    #+#             */
/*   Updated: 2022/02/06 03:07:34 by madorna-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int
	save_char(t_mini *mini, t_chars *chars)
{
	if (!*mini->line_cpy)
	{
		free(chars);
		return (1);
	}
	chars->c = *mini->line_cpy;
	chars->flag = mini->flag;
	if (!mini->chars)
		mini->chars = ft_lstnew(chars);
	else
		ft_lstadd_back(&mini->chars, ft_lstnew(chars));
	if (*mini->line_cpy)
		mini->line_cpy++;
	return (0);
}
