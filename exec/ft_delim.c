/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_delim.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madorna- <madorna-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 04:12:29 by madorna-          #+#    #+#             */
/*   Updated: 2022/02/13 04:12:45 by madorna-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void
	ft_delim(t_mini *mini)
{
	t_list	*l_delim;
	t_list	*begin_node;

	l_delim = mini->delimiters;
	begin_node = l_delim;
	while (l_delim)
	{
		if (mini->line && *mini->line && !ft_strncmp(l_delim->content,
				mini->line, ft_strlen(mini->line) + 1))
			l_delim = l_delim->next;
		promt(mini, 1);
		if (mini->line)
		{
			if (!ft_strncmp(l_delim->content, mini->line,
					ft_strlen(mini->line) + 1))
				l_delim = l_delim->next;
			else
				l_delim = begin_node;
			continue ;
		}
		printf("%s: warning: unexpected '\\0' (wanted `%s')\n", SHELL_NAME,
			(char *)l_delim->content);
		l_delim = l_delim->next;
		begin_node = l_delim;
	}
}
