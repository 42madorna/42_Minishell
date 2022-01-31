/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_to_lst.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madorna- <madorna-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 01:38:49 by madorna-          #+#    #+#             */
/*   Updated: 2022/01/31 02:55:46 by madorna-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void
	ft_env_to_lst(t_mini *mini)
{
	char	**env_var;
	t_env	*env_node;
	int		i;

	i = -1;
	while (mini->env[++i])
	{
		env_var = ft_split(mini->env[i], '=');
		env_node = calloc(1, sizeof(t_env));
		// if (!env_node)
		// 	printf("Error: Could not allocate memory for env_node");
		env_node->key = env_var[0];
		env_node->value = env_var[1];
		ft_lstadd_back(&mini->l_env, ft_lstnew(env_node));
		// Uncoment this to see each env var key:value
		// printf("key %s, value %s\n", env_node->key, env_node->value);
	}
}
