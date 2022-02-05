/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_finder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madorna- <madorna-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 18:07:44 by madorna-          #+#    #+#             */
/*   Updated: 2022/02/05 18:31:58 by madorna-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void
	print(void *lst)
{
	t_chars *chars;

	chars = lst;
	printf("node content '%c%c', flag '%d'\n", chars->c == 0 ? '\\' : chars->c, chars->c == 0 ? '0' : '\0' , chars->flag);
}

int
	quote_finder(t_mini *mini)
{
	t_chars	*chars;
	char	*buff_cpy;

	mini->line_cpy = ft_strtrim(mini->line, " ");
	buff_cpy = mini->line_cpy;
	while (*mini->line_cpy)
	{
		chars = calloc(1, sizeof(t_chars));
		if (*mini->line_cpy == '"')
			mini->p[DQUOTE](mini);
		if (*mini->line_cpy == '\'')
			mini->p[QUOTE](mini);
		if (!*mini->line_cpy)
		{
			free(chars);
			break ;
		}
		chars->c = *mini->line_cpy;
		chars->flag = mini->flag;
		ft_lstadd_back(&mini->chars, ft_lstnew(chars));
		mini->line_cpy++;
	}
	chars = calloc(1, sizeof(t_chars));
	chars->flag = 0;
	chars->c = '\0';
	ft_lstadd_back(&mini->chars, ft_lstnew(chars));
	free(buff_cpy);
	// Uncomment this to see what does mini->chars have
	ft_lstiter(mini->chars, print);
}