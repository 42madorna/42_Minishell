/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flagger.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madorna- <madorna-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 02:48:26 by madorna-          #+#    #+#             */
/*   Updated: 2022/02/09 07:30:04 by madorna-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void
	print(void *lst)
{
	t_chars	*chars;

	chars = lst;
	printf("node content '%c%c', flag '%d'\n", chars->c == 0 ? '\\' : chars->c,
		chars->c == 0 ? '0' : '\0', chars->flag);
}

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
	// Uncomment this to see what does mini->chars have
	// ft_lstiter(mini->chars, print);
	free(mini->buffer);
	mini->buffer = NULL;
	command_split(mini);
	ft_lstclear(&mini->chars, free);
	mini->chars = NULL;
}
