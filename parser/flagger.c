/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flagger.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madorna- <madorna-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 02:48:26 by madorna-          #+#    #+#             */
/*   Updated: 2022/02/11 21:12:18 by madorna-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void
	flagger(t_mini *mini)
{
	t_chars	*chars;

	ft_lstclear(&mini->chars, free);
	mini->line_cpy = mini->buffer;
	while (*mini->line_cpy)
	{
		chars = calloc(1, sizeof(t_chars));
		if (*mini->line_cpy == '"')
			mini->p[DQUOTE](mini);
		if (*mini->line_cpy == '\'')
			mini->p[QUOTE](mini);
		if (save_char(mini, chars))
			break ;
	}
	chars = calloc(1, sizeof(t_chars));
	save_char(mini, chars);
	free(mini->buffer);
	mini->buffer = NULL;
	command_split(mini);
	ft_lstclear(&mini->chars, free);
	mini->chars = NULL;
}
