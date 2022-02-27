/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaliste <agaliste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 17:21:13 by agaliste          #+#    #+#             */
/*   Updated: 2022/02/27 17:21:32 by agaliste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void
	skip_lst_spaces(t_list **lst)
{
	while ((*lst) && ft_isspace(((t_chars *)(*lst)->content)->c))
		*lst = (*lst)->next;
}

int
	ft_is_valid_char(char c)
{
	return (c == ' ' || c == '\'' || c == '"' || c == '\t'
		|| c == '|' || c == '>' || c == '<' || c == '/');
}
