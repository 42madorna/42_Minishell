/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manager.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaliste <agaliste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 17:06:34 by agaliste          #+#    #+#             */
/*   Updated: 2022/02/27 17:19:06 by agaliste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int
	manage_out(t_mini *mini, t_list **chars)
{
	char	*file;
	int		fd;

	mini->open_style = O_WRONLY | O_CREAT | O_TRUNC;
	*chars = (*chars)->next;
	if (*chars && ((t_chars *)((*chars)->content))->c == '>')
	{
		mini->open_style = O_APPEND | O_CREAT | O_WRONLY;
		*chars = (*chars)->next;
	}
	file = seek_name(mini, chars, OUT);
	if (!file && !mini->parse_err)
	{
		printf("Unexpected token near `%s'\n", unclosed_name(OUT));
		mini->parse_err = 1;
	}
	fd = open(file, mini->open_style, 0644);
	free(file);
	return (fd);
}

static inline int
	manage_in_helper(char *file, t_mini *mini, int flag, int *fd)
{
	if (!file)
	{
		printf("Unexpected token near `%s'\n", unclosed_name(IN));
		mini->parse_err = 1;
	}
	if (flag == APPEND)
	{
		if (file)
			ft_lstadd_back(&mini->delimiters, ft_lstnew(file));
		return (STDIN_FILENO);
	}
	*fd = open(file, mini->open_style, 0644);
	if (*fd < 0 && file)
	{
		printf("%s: %s: No such file or directory\n", SHELL_NAME, file);
		mini->parse_err = 1;
	}
	free(file);
	return (*fd);
}

int
	manage_in(t_mini *mini, t_list **chars)
{
	char	*file;
	int		fd;
	int		flag;

	flag = IN;
	mini->open_style = O_RDONLY;
	*chars = (*chars)->next;
	if (*chars && ((t_chars *)((*chars)->content))->c == '<')
	{
		flag = APPEND;
		*chars = (*chars)->next;
	}
	file = seek_name(mini, chars, IN);
	return (manage_in_helper(file, mini, flag, &fd));
}

void
	manage_pipe(t_mini *mini, t_list **chars)
{
	t_chars	*chars_node;

	*chars = (*chars)->next;
	skip_lst_spaces(chars);
	if (!(*chars) || !(*chars)->next)
	{
		printf("Unexpected token near `%s'\n", unclosed_name(PIPE));
		mini->parse_err = 1;
		return ;
	}
	chars_node = (*chars)->content;
	if (!chars_node || chars_node->c == '|')
	{
		printf("Unexpected token near `%s'\n", unclosed_name(PIPE));
		mini->parse_err = 1;
	}
}