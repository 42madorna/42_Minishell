/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_finder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madorna- <madorna-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 18:07:44 by madorna-          #+#    #+#             */
/*   Updated: 2022/02/06 02:50:45 by madorna-         ###   ########.fr       */
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

int
	ft_search_pair(t_list **l_chars, int flag, char find)
{
	t_chars	*chars;
	t_list	*char_node;

	char_node = *l_chars;
	while (char_node)
	{
		chars = char_node->content;
		if (chars->c == find && chars->flag == 0)
			return (0);
		char_node = char_node->next;
	}
	return (flag);
}

int
	ft_search_unclosed_q(t_list *l_chars)
{
	t_chars	*chars;
	int		unclosed_ret;

	unclosed_ret = 0;
	while (l_chars)
	{
		chars = l_chars->content;
		if (chars->c == '\'' && chars->flag == QUOTE)
		{
			unclosed_ret = ft_search_pair(&l_chars, QUOTE, '\'');
			if (unclosed_ret)
				return (unclosed_ret);
		}
		if (chars->c == '"' && chars->flag == DQUOTE)
		{
			unclosed_ret = ft_search_pair(&l_chars, DQUOTE, '"');
			if (unclosed_ret)
				return (unclosed_ret);
		}
		l_chars = l_chars->next;
	}
	return (0);
}

int
	quote_finder(t_mini *mini)
{
	t_chars	*chars;
	char	*buff_cpy;
	int		unclosed;

	mini->line_cpy = ft_strtrim(mini->line, " ");
	buff_cpy = mini->line_cpy;
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
	free(buff_cpy);
	// Uncomment this to see what does mini->chars have
	// ft_lstiter(mini->chars, print);
	unclosed = ft_search_unclosed_q(mini->chars);
	if (unclosed)
		printf("Unexpected %s\n", unclosed_name(unclosed));
	dollar_finder(mini);
}
