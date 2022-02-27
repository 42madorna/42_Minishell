/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   seeker.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaliste <agaliste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 17:06:29 by agaliste          #+#    #+#             */
/*   Updated: 2022/02/27 18:11:15 by agaliste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static inline char
	*seek_name_helper(char **name, t_list **chars, t_chars **chars_node)
{
	int	i;

	i = 0;
	if (*chars && !ft_isspace(((t_chars *)((*chars)->content))->c)
		&& ((t_chars *)((*chars)->content))->c != '>')
		*name = ft_calloc(1024, sizeof(char));
	else
		return (NULL);
	while (*chars)
	{
		(*chars_node) = (*chars)->content;
		if (ft_is_valid_char((*chars_node)->c)
			&& (*chars_node)->flag != DQUOTE && (*chars_node)->flag != QUOTE)
			break ;
		*name[i++] = (*chars_node)->c;
		(*chars) = (*chars)->next;
	}
	if (**name == '\'' || **name == '"')
		ft_memcpy(*name, *name + 1, i);
	if (*name[ft_strlen(*name) - 1] == '\''
		|| *name[ft_strlen(*name) - 1] == '"')
		*name[ft_strlen(*name) - 1] = '\0';
	return (*name);
}

char
	*seek_name(t_mini *mini, t_list **chars, int flag)
{
	t_chars	*chars_node;
	char	*name;

	while (*chars)
	{
		chars_node = (*chars)->content;
		if (chars_node->c == '>' || chars_node->c == '<'
			|| chars_node->c == '|' || chars_node->c == '\0')
		{
			printf("Unexpected token near `%s'\n", unclosed_name(flag));
			mini->parse_err = 1;
			break ;
		}
		if (!ft_isspace(chars_node->c))
			break ;
		(*chars) = (*chars)->next;
	}
	return (seek_name_helper(&name, chars, &chars_node));
}
