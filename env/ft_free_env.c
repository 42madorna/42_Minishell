/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madorna- <madorna-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 04:19:49 by madorna-          #+#    #+#             */
/*   Updated: 2022/02/06 05:16:13 by madorna-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static inline char
	**ft_malloc_error(char **tab, t_env *env_node)
{
	unsigned int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		tab[i] = NULL;
		i++;
	}
	env_node->key = NULL;
	env_node->value = NULL;
	free(tab);
	tab = NULL;
	return (NULL);
}

void
	ft_free_env(void *env)
{
	t_env	*env_node;

	env_node = env;
	if (env_node->split_mem)
		ft_malloc_error(env_node->split_mem, env_node);
	if (env_node->key)
		free(env_node->key);
	env_node->key = NULL;
	if (env_node->value)
		free(env_node->value);
	env_node->value = NULL;
	env_node->split_mem = NULL;
	if (env)
		free(env);
	env = NULL;
}
