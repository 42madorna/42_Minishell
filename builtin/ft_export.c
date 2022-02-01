/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madorna- <madorna-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/11 06:17:31 by madorna-          #+#    #+#             */
/*   Updated: 2022/02/01 19:35:47 by madorna-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char
	**free_malloc(char **tab)
{
	unsigned int	i;

	i = 0;
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
	// if (!a->key)
	// 	return (1);
	// if (!b->key)
	// 	return (0);
	return (strcmp(a->key, b->key) > 0);
}

t_list
	*ft_find_max(t_list *l_env)
{
	t_list	*min;

	min = l_env;
	while (l_env)
	{
		if (cmp_env(((t_env*)(l_env)->content), ((t_env*)(min)->content)))
			min = l_env;
		l_env = l_env->next;
	}
	return (min);
}

t_list
	*ft_lstsort(t_list *l_env)
{
	t_list	*sorted;
	t_list	*max;
	t_list	*env_node;

	while (l_env)
	{
		max = ft_find_max(l_env);
		if (max == l_env)
			l_env = l_env->next;
		else
		{
			env_node = l_env;
			while (env_node->next != max)
				env_node = env_node->next;
			env_node->next = max->next;
		}
		max->next = sorted;
		sorted = max;
	}
	return (sorted);
}

// void
// 	clear_env(void *env)
// {
// 	t_env	*clear;

// 	clear = env;
// 	if (clear->name)
// 	{
// 		free(clear->name);
// 		clear->name = NULL;
// 	}
// 	if (clear->value)
// 	{
// 		free(clear->value);
// 		clear->value = NULL;
// 	}
// }

/*
** builtin: export
** export -> prints "declare -x" and then, env variable. Env variables are
** 	sorted using their name using ascii.
** export (name) -> prints '\n' and then, adds (name) to env vars.
** More than the first parametter has to be handled
** ! Although env prints just env variables with value, env prints everything
** 	even if there is no value set for that env variable.
*/

static inline void
	print_env_list(t_list *l_env)
{
	t_list	*env_node;

	env_node = l_env;
	while (env_node)
	{
		/*
		** TODO: [MINS-83]
		*/
		// if (!((t_env *)(env_node->content)))
		// 	break ;
		if (((t_env *)(env_node->content))->value)
			printf("declare -x %s=\"%s\"\n", ((t_env *)(env_node->content))->key,
				((t_env *)(env_node->content))->value);
		else
			printf("declare -x %s\n", ((t_env *)(env_node->content))->key);
		env_node = env_node->next;
	}
}

int
	ft_export(int argc, char **argv, t_list *env)
{
	char	**arg;
	t_list	*cpy;
	int		i;


	/*
	** FIXME: Export should not modify existing env vars
	*/
	if (argc >= 2)
	{
		i = 1;
		while (argv[i])
		{
			arg = ft_split(argv[i], '=');
			ft_env_set_value(env, arg[0], arg[1]);
			free_malloc(arg);
			++i;
		}
		return (0);
	}
	/*
	** FIXME: sorting makes minishell crash
	*/
	// cpy = calloc(1, sizeof(t_list));
	// cpy = ft_memcpy(cpy, env, sizeof(t_list));
	// ft_lstsort(cpy);
	print_env_list(env);
	return (0);
}
