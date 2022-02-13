/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madorna- <madorna-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/11 06:17:31 by madorna-          #+#    #+#             */
/*   Updated: 2022/02/13 20:56:29 by madorna-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char
	**free_malloc(char **tab)
{
	unsigned int	i;

	i = 0;
	if (!tab)
		return (NULL);
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (NULL);
}

static inline int
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

inline static void
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

/*
** builtin: export
** export -> prints "declare -x" and then, env variable. Env variables are
** 	sorted using their name using ascii.
** export (name) -> prints '\n' and then, adds (name) to env vars.
** More than the first parametter has to be handled
** ! Although env prints just env variables with value, export prints everything
** 	even if there is no value set for that env variable.
*/

static inline void
	print_env_list(t_list *l_env)
{
	t_list	*env_node;

	env_node = l_env;
	while (env_node)
	{
		if (((t_env *)(env_node->content))->value)
			printf("declare -x %s=\"%s\"\n", ((t_env *)(env_node->content))->key,
				((t_env *)(env_node->content))->value);
		else
			printf("declare -x %s\n", ((t_env *)(env_node->content))->key);
		env_node = env_node->next;
	}
}

static inline t_list
	*lst_cpy(t_list *lst)
{
	t_list	*cpy;
	t_list	*lst_node;

	if (!lst)
		return (NULL);
	lst_node = lst;
	cpy = ft_lstnew(lst_node->content);
	lst_node = lst_node->next;
	while (lst_node)
	{
		ft_lstadd_back(&cpy, ft_lstnew(lst_node->content));
		lst_node = lst_node->next;
	}
	return (cpy);
}

int
	ft_is_valid_identifier(char *str)
{
	return (!ft_isalpha(*str));
}

int
	ft_export(int argc, char **argv, t_list *env)
{
	char	**arg;
	t_list	*cpy;
	int		i;

	(void)cpy;
	if (argc >= 2)
	{
		i = 0;
		while (argv[i++])
		{
			arg = ft_split(argv[i], '=');
			if (arg && arg[0])
			{
				if (ft_is_valid_identifier(arg[0]))
				{
					dprintf(2, "%s: export: `%s': not a valid identifier\n",
						SHELL_NAME, arg[0]);
					free_malloc(arg);
					continue ;
				}
			}
			free_malloc(arg);
		}
		return (0);
	}
	cpy = lst_cpy(env);
	ft_lstsort(cpy);
	print_env_list(cpy);
	return (0);
}
