/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madorna- <madorna-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/11 06:17:31 by madorna-          #+#    #+#             */
/*   Updated: 2021/08/01 02:46:25 by madorna-         ###   ########.fr       */
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
	if (!a->name)
		return (1);
	if (!b->name)
		return (0);
	return (ft_strcmp(a->name, b->name) > 0);
}

void
	clear_env(void *env)
{
	t_env	*clear;

	clear = env;
	if (clear->name)
	{
		free(clear->name);
		clear->name = NULL;
	}
	if (clear->value)
	{
		free(clear->value);
		clear->value = NULL;
	}
}

/*
** builtin: export
** export -> prints "declare -x" and then, env variable. Env variables are
** 	sorted using their name using ascii.
** export (name) -> prints '\n' and then, adds (name) to env vars.
** More than the first parametter has to be handled
** ! Although env prints just env variables with value, env prints everything
** 	even if there is no value set for that env variable.
*/

int
	ft_export(int argc, char **argv, t_list *env)
{
	char	**arg;
	t_list	*cpy;
	int		i;

	write(1, "\n", 1);
	if (argc >= 2)
	{
		i = 1;
		while (argv[i])
		{
			arg = ft_split(argv[i], '=');
			set_value(env, arg[0], arg[1], (char *)__FUNCTION__);
			free_malloc(arg);
			++i;
		}
		return (0);
	}
	cpy = calloc(1, sizeof(t_list));
	ft_memcpy(cpy, env, sizeof(t_list));
	ft_lstsort(cpy, cmp_env);
	print_env_list(cpy, __FUNCTION__);
	return (0);
}