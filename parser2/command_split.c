/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madorna- <madorna-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 05:30:40 by madorna-          #+#    #+#             */
/*   Updated: 2022/02/06 08:25:05 by madorna-         ###   ########.fr       */
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

static int
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
	return (fd);
}

static int
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
	return (fd);
}

static void
	manage_pipe(t_mini *mini, t_list **chars)
{
	t_chars	*chars_node;

	printf("Found |\n");
	*chars = (*chars)->next;
}

static inline void
	skip_lst_spaces(t_list **lst)
{
	while ((*lst) && ft_isspace(((t_chars*)(*lst)->content)->c))
		*lst = (*lst)->next;
}

void
	command_split(t_mini *mini)
{
	t_list	*chars;
	t_chars	*chars_node;
	t_cmd	*cmd;
	char	*arg;
	int		i;

	chars = mini->chars;
	cmd = calloc(1, sizeof(t_cmd));
	i = 0;
	arg = calloc(1024, sizeof(char));
	while (chars)
	{
		chars_node = chars->content;
		if (chars_node->c == '|' && chars_node->flag != QUOTE
			&& chars_node->flag != DQUOTE)
		{
			if (arg)
			{
				if (*arg == '\'' || *arg == '"')
					ft_memcpy(arg, arg + 1, i);
				if (ft_strlen(arg) > 0)
				{
					if (arg[ft_strlen(arg) - 1] == '\'' || arg[ft_strlen(arg) - 1] == '"')
						arg[ft_strlen(arg) - 1] = '\0';
					if (*arg)
						ft_lstadd_back(&cmd->l_argv, ft_lstnew(arg));
				}
				if (*arg)
					ft_lstadd_back(&cmd->l_argv, ft_lstnew(arg));
			}
			arg = calloc(1024, sizeof(char));
			i = 0;
			manage_pipe(mini, &chars);
			ft_lstadd_back(&mini->cmds, ft_lstnew(cmd));
			cmd = calloc(1, sizeof(t_cmd));
			continue ;
		}
		if (chars_node->c == '>' && chars_node->flag != QUOTE
			&& chars_node->flag != DQUOTE)
		{
			if (arg)
			{
				if (*arg == '\'' || *arg == '"')
					ft_memcpy(arg, arg + 1, i);
				if (ft_strlen(arg) > 0)
				{
					if (arg[ft_strlen(arg) - 1] == '\'' || arg[ft_strlen(arg) - 1] == '"')
						arg[ft_strlen(arg) - 1] = '\0';
					if (*arg)
						ft_lstadd_back(&cmd->l_argv, ft_lstnew(arg));
				}
				if (*arg)
					ft_lstadd_back(&cmd->l_argv, ft_lstnew(arg));
			}
			arg = calloc(1024, sizeof(char));
			i = 0;
			cmd->outfile = manage_out(mini, &chars);
			continue ;
		}
		if (chars_node->c == '<' && chars_node->flag != QUOTE
			&& chars_node->flag != DQUOTE)
		{
			if (arg)
			{
				if (*arg == '\'' || *arg == '"')
					ft_memcpy(arg, arg + 1, i);
				if (ft_strlen(arg) > 0)
				{
					if (arg[ft_strlen(arg) - 1] == '\'' || arg[ft_strlen(arg) - 1] == '"')
						arg[ft_strlen(arg) - 1] = '\0';
					if (*arg)
						ft_lstadd_back(&cmd->l_argv, ft_lstnew(arg));
				}
				if (*arg)
					ft_lstadd_back(&cmd->l_argv, ft_lstnew(arg));
			}
			arg = calloc(1024, sizeof(char));
			i = 0;
			cmd->infile = manage_in(mini, &chars);
			continue ;
		}
		if (chars_node->c == ' ' && chars_node->flag != QUOTE
			&& chars_node->flag != DQUOTE)
		{
			
			if (arg)
			{
				if (*arg == '\'' || *arg == '"')
					ft_memcpy(arg, arg + 1, i);
				if (ft_strlen(arg) > 0)
				{
					if (arg[ft_strlen(arg) - 1] == '\'' || arg[ft_strlen(arg) - 1] == '"')
						arg[ft_strlen(arg) - 1] = '\0';
					if (*arg)
						ft_lstadd_back(&cmd->l_argv, ft_lstnew(arg));
				}
			}
			arg = calloc(1024, sizeof(char));
			i = 0;
			skip_lst_spaces(&chars);
			continue ;
		}
		arg[i++] = chars_node->c;
		chars = chars->next;
	}
	if (arg)
	{
		if (*arg == '\'' || *arg == '"')
			ft_memcpy(arg, arg + 1, i);
		if (ft_strlen(arg) > 0)
		{
			if (arg[ft_strlen(arg) - 1] == '\'' || arg[ft_strlen(arg) - 1] == '"')
				arg[ft_strlen(arg) - 1] = '\0';
			if (*arg)
				ft_lstadd_back(&cmd->l_argv, ft_lstnew(arg));
		}
	}
	ft_lstadd_back(&mini->cmds, ft_lstnew(cmd));
}