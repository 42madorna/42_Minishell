/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madorna- <madorna-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/11 04:06:40 by madorna-          #+#    #+#             */
/*   Updated: 2022/02/05 01:37:25 by madorna-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** builtin: unset
** unset does an unset of a variable -> unset VAR
** It prints nothing even if the environment variable does not exist.
** Keep in mind that unset is not meant to work with options as the subject
** 	says.
** Unset should delete the entry from env variables, not just setting a NULL
** 	value.
** Unset takes just the first argument, ignores the rest.
*/

void
	ft_del_env_node(void *env)
{
	t_env	*env_node;

	env_node = env;
	if (env_node->key)
	{
		free(env_node->key);
		env_node->key = NULL;
	}
	if (env_node->value)
	{
		free(env_node->value);
		env_node->value = NULL;
	}
}
/*
** TODO: Remove env variable
*/
void
	del_env_vble(t_list *l_env, char *str)
{
	t_list	*env_node;
	t_list	*del;

	env_node = l_env;
	while (env_node)
	{
		if (!ft_strncmp(((t_env *)env_node->content)->key, str, ft_strlen(((t_env *)env_node->content)->key)))
		{
			del = env_node;
			break ;
		}
		env_node = env_node->next;
	}
	ft_lstdelone(del, ft_del_env_node);
}

int
	ft_unset(int argc, char **argv, t_list *l_env)
{
	// write(1, "\n", 1);
	// if (argc >= 2)
	// 	del_env_vble(l_env, argv[1]);
	printf("TODO: [MINS-77] unset builtin\n");
	return (0);
}
