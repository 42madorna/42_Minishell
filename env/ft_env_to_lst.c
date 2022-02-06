/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_to_lst.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madorna- <madorna-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 01:38:49 by madorna-          #+#    #+#             */
/*   Updated: 2022/02/06 19:30:45 by madorna-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static inline int
	ft_has_env_var(t_mini *mini, char *str)
{
	t_list	*env_node;
	t_env	*env_cont;

	env_node = mini->l_env;
	while (env_node)
	{
		env_cont = env_node->content;
		if (!ft_strncmp(env_cont->key, str, ft_strlen(str) + 1))
			return (1);
		env_node = env_node->next;
	}
	return (0);
}

static inline void
	ft_add_basic_env(t_mini *mini)
{
	t_env	*env_node;

	if (!ft_has_env_var(mini, "OLDPWD"))
	{
		env_node = calloc(1, sizeof(t_env));
		env_node->key = ft_strdup("OLDPWD");
		env_node->value = ft_strdup("");
		ft_lstadd_back(&mini->l_env, ft_lstnew(env_node));
	}
	if (!ft_has_env_var(mini, "PWD"))
	{
		env_node = calloc(1, sizeof(t_env));
		env_node->key = ft_strdup("PWD");
		env_node->value = getcwd(env_node->value, 0);
		ft_lstadd_back(&mini->l_env, ft_lstnew(env_node));
	}
	if (!ft_has_env_var(mini, "SHLVL"))
	{
		env_node = calloc(1, sizeof(t_env));
		env_node->key = ft_strdup("SHLVL");
		env_node->value = ft_strdup("1");
		ft_lstadd_back(&mini->l_env, ft_lstnew(env_node));
	}
}

void
	ft_env_to_lst(t_mini *mini)
{
	t_env	*env_node;
	int		i;

	i = -1;
	while (mini->env[++i])
	{
		env_node = calloc(1, sizeof(t_env));
		env_node->split_mem = ft_split(mini->env[i], '=');
		// if (!env_node)
		// 	printf("Error: Could not allocate memory for env_node");
		env_node->key = env_node->split_mem[0];
		env_node->value = env_node->split_mem[1];
		ft_lstadd_back(&mini->l_env, ft_lstnew(env_node));
		// Uncomment this to see each env var key:value
		// printf("key %s, value %s\n", env_node->key, env_node->value);
	}
	ft_add_basic_env(mini);
}
