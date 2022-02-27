/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaliste <agaliste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 05:30:40 by madorna-          #+#    #+#             */
/*   Updated: 2022/02/27 18:42:51 by agaliste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void
	arg_fix(char **arg, int *i, t_cmd *cmd)
{
	if (arg && *arg && **arg)
	{
		if (**arg == '\'' || **arg == '"')
			ft_memcpy(*arg, *arg + 1, *i);
		if (*i > 0)
		{
			if (*(*(arg) + (*i - 1)) == '\'' || *(*(arg) + (*i - 1)) == '"')
				*(*(arg) + (*i - 1)) = '\0';
			if (**arg)
				ft_lstadd_back(&cmd->l_argv, ft_lstnew(ft_strdup(*arg)));
		}
	}
	free(*arg);
	*arg = calloc(1024, sizeof(char *));
	*i = 0;
}

static inline int
	command_split_while1(t_mini *mini, t_list **chars, int *i, t_cmd **cmd)
{
	t_chars	*chars_node;

	chars_node = (*chars)->content;
	if (chars_node->c == '|' && chars_node->flag != QUOTE
		&& chars_node->flag != DQUOTE)
	{
		manage_pipe(mini, &(*chars));
		arg_fix(&mini->arg, &(*i), (*cmd));
		(*cmd)->num = ft_lstsize(mini->cmds);
		ft_lstadd_back(&mini->cmds, ft_lstnew((*cmd)));
		(*cmd) = calloc(1, sizeof(t_cmd));
		return (1);
	}
	if (chars_node->c == '>' && chars_node->flag != QUOTE
		&& chars_node->flag != DQUOTE)
	{
		(*cmd)->outfile = manage_out(mini, &(*chars));
		arg_fix(&mini->arg, &(*i), (*cmd));
		return (1);
	}
	return (0);
}

static inline void
	command_split_while2(t_mini *mini, t_list **chars, int *i, t_cmd **cmd)
{
	t_chars	*chars_node;

	chars_node = (*chars)->content;
	if (chars_node->c == '<' && chars_node->flag != QUOTE
		&& chars_node->flag != DQUOTE)
	{
		(*cmd)->infile = manage_in(mini, &(*chars));
		arg_fix(&mini->arg, &(*i), (*cmd));
		return ;
	}
	if (chars_node->c == ' ' && chars_node->flag != QUOTE
		&& chars_node->flag != DQUOTE)
	{
		skip_lst_spaces(&(*chars));
		arg_fix(&mini->arg, &(*i), (*cmd));
		return ;
	}
	if (!(chars_node->c == '"' && (chars_node->flag == DQUOTE
				|| chars_node->flag == 0)) && !(chars_node->c == '\''
			&& (chars_node->flag == QUOTE || chars_node->flag == 0)))
		mini->arg[(*i)++] = chars_node->c;
	*chars = (*chars)->next;
}

static inline void
	command_split_helper(t_cmd **cmd, int *i, t_mini *mini)
{
	if (mini->arg)
	{
		if (*mini->arg == '\'' || *mini->arg == '"')
			ft_memcpy(mini->arg, mini->arg + 1, (*i));
		if ((*i) > 0)
		{
			if (mini->arg[(*i) - 1] == '\''
				|| mini->arg[(*i) - 1] == '"')
				mini->arg[(*i) - 1] = '\0';
			if (*mini->arg)
				ft_lstadd_back(&(*cmd)->l_argv,
					ft_lstnew(ft_strdup(mini->arg)));
		}
		free(mini->arg);
	}
	(*cmd)->num = ft_lstsize(mini->cmds);
	ft_lstadd_back(&mini->cmds, ft_lstnew((*cmd)));
}

void
	command_split(t_mini *mini)
{
	t_chars	*chars_node;
	t_list	*chars;
	t_cmd	*cmd;
	int		i;

	chars = mini->chars;
	if (!chars)
		return ;
	cmd = calloc(1, sizeof(t_cmd));
	i = 0;
	mini->arg = calloc(1024, sizeof(char *));
	chars_node = chars->content;
	if (chars_node->c == '|')
	{
		printf("Unexpected token near `%s'\n", unclosed_name(PIPE));
		mini->parse_err = 1;
		return ;
	}
	while (chars && !mini->parse_err)
	{
		if (!command_split_while1(mini, &chars, &i, &cmd))
			command_split_while2(mini, &chars, &i, &cmd);
	}
	command_split_helper(&cmd, &i, mini);
}
