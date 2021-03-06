/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_finder.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madorna- <madorna-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 01:35:39 by madorna-          #+#    #+#             */
/*   Updated: 2022/03/08 16:58:10 by madorna-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void
	ft_save_name(t_list **lst, t_mini *mini, int *i, char *env_var)
{
	while ((*lst) && !ft_is_valid_char(((t_chars *)(*lst)->content)->c)
		&& !mini->parse_err)
	{
		if ((*i) == 0 && ft_isdigit(((t_chars *)(*lst)->content)->c))
		{
			printf("Unexpected token\n");
			mini->parse_err = 1;
		}
		if (!ft_isalnum(((t_chars *)(*lst)->content)->c)
			&& ((t_chars *)(*lst)->content)->c != '?'
			&& ((t_chars *)(*lst)->content)->c != '_')
		{
			printf("Unexpected token\n");
			mini->parse_err = 1;
		}
		env_var[(*i)++] = ((t_chars *)(*lst)->content)->c;
		*lst = (*lst)->next;
	}
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
	ft_save_name(lst, mini, &i, env_var);
	env_cont = ft_env_value(mini->l_env, env_var);
	if (!ft_strncmp("?\0", env_var, 2))
		env_cont = ft_itoa(mini->ret);
	env_cont_cpy = env_cont;
	if (i == 0 && (!*lst || (((t_chars *)(*lst)->content)->c != '"'
			&& ((t_chars *)(*lst)->content)->c != '\'')))
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
	mini->buffer = calloc(1024, sizeof(char *));
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
	if (!mini->parse_err)
		flagger(mini);
}
