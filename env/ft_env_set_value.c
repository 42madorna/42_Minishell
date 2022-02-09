/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_set_value.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madorna- <madorna-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 18:11:23 by madorna-          #+#    #+#             */
/*   Updated: 2022/02/09 04:32:21 by madorna-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void
	ft_env_new(t_list *l_env, char *new_key, char *new_value)
{
	t_env *env_node;

	env_node = calloc(1, sizeof(t_env));
	env_node->key = ft_strdup(new_key);
	if (new_value)
		env_node->value = ft_strdup(new_value);
	ft_lstadd_back(&l_env, ft_lstnew(env_node));
}

void
	ft_env_set_value(t_list *l_env, char *key, char *new_value)
{
	t_list	*env_node;

	env_node = l_env;
	while (env_node)
	{
		if (!ft_strncmp(((t_env *)(env_node->content))->key, key,
			ft_strlen(((t_env *)(env_node->content))->key)))
		{
			free(((t_env *)(env_node->content))->value);
			((t_env *)(env_node->content))->value = NULL;
			if (new_value)
				((t_env *)(env_node->content))->value = ft_strdup(new_value);
			return ;
		}
		env_node = env_node->next;
	}
	ft_env_new(l_env, key, new_value);
}
