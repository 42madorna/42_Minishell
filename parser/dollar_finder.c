/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_finder.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madorna- <madorna-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 01:35:39 by madorna-          #+#    #+#             */
/*   Updated: 2022/02/09 07:52:23 by madorna-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static inline int
	ft_is_valid_char(char c)
{
	return (c == ' ' || c == '\'' || c == '"' || c == '\t'
		|| c == '|' || c == '>' || c == '<' || c == '/');
}

static inline void
	manage_dollar(t_mini *mini, t_list **lst, int *pos)
{
	char	*env_var;
	char	*env_cont;
	char	*env_cont_cpy;
	int		i;

	i = 0;
	env_var = calloc(1024, sizeof(char));
	while ((*lst) && !ft_is_valid_char(((t_chars*)(*lst)->content)->c))
	{
		if (i == 0 && ft_isdigit(((t_chars*)(*lst)->content)->c))
		{
			printf("Unexpected token\n");
			mini->parse_err = 1;
		}
		if (!ft_isalnum(((t_chars*)(*lst)->content)->c) && ((t_chars*)(*lst)->content)->c != '?')
		{
			printf("Unexpected token\n");
			mini->parse_err = 1;
		}
		env_var[i++] = ((t_chars*)(*lst)->content)->c;
		*lst = (*lst)->next;
	}
	env_cont = ft_env_value(mini->l_env, env_var);
	env_cont_cpy = env_cont;
	if (!ft_strncmp("?\0", env_var, 2))
		env_cont = ft_itoa(mini->ret);
	if (i == 0 && (!*lst || (((t_chars*)(*lst)->content)->c != '"' && ((t_chars*)(*lst)->content)->c != '\'')))
		env_cont = "$";
	while (env_cont && *env_cont)
		mini->buffer[(*pos)++] = *env_cont++;
	free(env_var);
	free(env_cont_cpy);
}

void
	dollar_finder(t_mini *mini)
{
	t_list	*l_chars;
	t_chars	*chars_node;
	int		i;

	l_chars = mini->chars;
	mini->buffer = calloc(1024, sizeof(char*));
	i = 0;
	while (l_chars && !mini->parse_err)
	{
		chars_node = l_chars->content;
		if (chars_node->c == '$' && chars_node->flag != QUOTE)
		{
			l_chars = l_chars->next;
			manage_dollar(mini, &l_chars, &i);
			continue ;
		}
		mini->buffer[i++] = chars_node->c;
		l_chars = l_chars->next;
	}
	// printf("mini->buff %s\n", mini->buffer);
	if (!mini->parse_err)
		flagger(mini);
}