/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madorna- <madorna-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/11 04:06:40 by madorna-          #+#    #+#             */
/*   Updated: 2022/03/03 19:53:36 by madorna-         ###   ########.fr       */
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
	free(env_node);
}

inline static void
	ft_repoint(t_list **l_env, t_list *del)
{
	t_list	*reseach;

	reseach = (*l_env);
	if ((*l_env) == del)
		(*l_env) = (*l_env)->next;
	else
	{
		while (reseach && reseach->next && del)
		{
			if (reseach->next == del)
			{
				reseach->next = del->next;
				break ;
			}
			reseach = reseach->next;
		}
	}
}

inline static void
	del_env_vble(t_list **l_env, char *str)
{
	t_list	*env_node;
	t_list	*del;

	env_node = (*l_env);
	del = NULL;
	while (env_node)
	{
		if (!ft_strncmp(((t_env *)env_node->content)->key,
				str, ft_strlen(((t_env *)env_node->content)->key) + 1))
		{
			del = env_node;
			break ;
		}
		env_node = env_node->next;
	}
	ft_repoint(l_env, del);
	ft_lstdelone(del, ft_del_env_node);
}

int
	ft_unset(int argc, char **argv, t_list **l_env)
{
	if (argc >= 2)
		del_env_vble(l_env, argv[1]);
	return (0);
}
