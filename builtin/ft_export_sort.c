/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_sort.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madorna- <madorna-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 00:48:09 by madorna-          #+#    #+#             */
/*   Updated: 2022/02/14 00:48:36 by madorna-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int
	cmp_env(t_env *a, t_env *b)
{
	if (!a || !b)
		return (0);
	if (!a->key)
		return (1);
	if (!b->key)
		return (0);
	return (ft_strncmp(a->key, b->key, ft_strlen(b->key) + 1) > 0);
}

t_list
	*ft_find_max(t_list *l_env)
{
	t_list	*min;

	min = l_env;
	while (l_env)
	{
		if (cmp_env(((t_env *)(l_env)->content), ((t_env *)(min)->content)))
			min = l_env;
		l_env = l_env->next;
	}
	return (min);
}

void
	ft_lstsort(t_list *l_env)
{
	t_list	*index;
	t_env	*temp;

	if (!l_env)
		return ;
	while (l_env)
	{
		index = l_env->next;
		while (index)
		{
			if (cmp_env(l_env->content, index->content))
			{
				temp = l_env->content;
				l_env->content = index->content;
				index->content = temp;
			}
			index = index->next;
		}
		l_env = l_env->next;
	}
}
