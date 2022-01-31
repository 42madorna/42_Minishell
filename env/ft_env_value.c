/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_value.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madorna- <madorna-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 02:22:17 by madorna-          #+#    #+#             */
/*   Updated: 2022/01/31 02:53:13 by madorna-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char
	*ft_env_value(t_mini *mini, const char *key)
{
	t_list	*env_node;
	int		key_len;

	key_len = ft_strlen(key) + 1;
	env_node = mini->l_env;
	while (env_node)
	{
		if (!ft_strncmp(((t_env *)env_node->content)->key, key, key_len))
			return (((t_env *)env_node->content)->value);
		env_node = env_node->next;
	}
	return (NULL);
}
