/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madorna- <madorna-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 05:30:40 by madorna-          #+#    #+#             */
/*   Updated: 2022/02/06 07:15:35 by madorna-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char
	*seek_name(t_mini *mini, t_list **chars, int flag)
{
	t_chars	*chars_node;
	char	*name;
	int		i;

	while (*chars)
	{
		chars_node = (*chars)->content;
		if (chars_node->c == '>' || chars_node->c == '<'
			|| chars_node->c == '|')
		{
			printf("Unexpected token near %s\n", unclosed_name(flag));
			break ;
		}
		if (!ft_isspace(chars_node->c))
			break ;
		(*chars) = (*chars)->next;
	}
	if (*chars && !ft_isspace(((t_chars *)((*chars)->content))->c)
		&& ((t_chars *)((*chars)->content))->c != '>')
		name = ft_calloc(1024, sizeof(char));
	else
		return (NULL);
	i = 0;
	while (*chars)
	{
		chars_node = (*chars)->content;
		if (ft_isspace(chars_node->c) && chars_node->flag != DQUOTE
			&& chars_node->flag  != QUOTE)
			break ;
		name[i++] = chars_node->c;
		(*chars) = (*chars)->next;
	}
	if (*name == '\'' || *name == '"')
		ft_memcpy(name, name + 1, i);
	if (name[ft_strlen(name) - 1] == '\'' || name[ft_strlen(name) - 1] == '"')
		name[ft_strlen(name) - 1] = '\0';
	return (name);
}

static void
	manage_out(t_mini *mini, t_list **chars)
{
	t_chars	*chars_node;
	char	*file;
	int		fd;

	printf("Found >\n");
	mini->open_style = O_WRONLY | O_CREAT;
	*chars = (*chars)->next;
	if (*chars && ((t_chars *)((*chars)->content))->c == '>')
	{
		printf("OH, it is an APPEND\n");
		mini->open_style = O_APPEND | O_CREAT | O_RDONLY | O_WRONLY;
		*chars = (*chars)->next;
	}
	file = seek_name(mini, chars, OUT);
	if (!file)
		printf("Unexpected token near %s\n", unclosed_name(OUT));
	fd = open(file, mini->open_style, 0644);
	free(file);
}

static void
	manage_in(t_mini *mini, t_list **chars)
{
	t_chars	*chars_node;
	char	*file;
	int		fd;

	printf("Found <\n");
	mini->open_style = O_RDONLY;
	*chars = (*chars)->next;
	if (*chars && ((t_chars *)((*chars)->content))->c == '<')
	{
		printf("OH, it is a DELIMITER\nTODO: MINS-57 P-Delimiter");
		*chars = (*chars)->next;
	}
	file = seek_name(mini, chars, IN);
	if (!file)
		printf("Unexpected token near %s\n", unclosed_name(IN));
	fd = open(file, mini->open_style, 0644);
	free(file);
}

static void
	manage_pipe(t_mini *mini, t_list **chars)
{
	t_chars	*chars_node;

	printf("Found |\n");
	*chars = (*chars)->next;
}

void
	command_split(t_mini *mini)
{
	t_list	*chars;
	t_chars	*chars_node;

	chars = mini->chars;
	while (chars)
	{
		chars_node = chars->content;
		if (chars_node->c == '|' && chars_node->flag != QUOTE && chars_node->flag != DQUOTE)
		{
			manage_pipe(mini, &chars);
			continue ;
		}
		if (chars_node->c == '>' && chars_node->flag != QUOTE && chars_node->flag != DQUOTE)
		{
			manage_out(mini, &chars);
			continue ;
		}
		if (chars_node->c == '<' && chars_node->flag != QUOTE && chars_node->flag != DQUOTE)
		{
			manage_in(mini, &chars);
			continue ;
		}
		chars = chars->next;
	}
}
