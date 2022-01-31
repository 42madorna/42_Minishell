/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madorna- <madorna-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 05:13:01 by madorna-          #+#    #+#             */
/*   Updated: 2022/01/31 18:06:43 by madorna-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** builtin: env
** env -> print environment variables
** Keep in mind that env is not meant to take arguments
** 	or optins as the subject says !
*/

void
	print_env_list(t_list *l_env)
{
	t_list	*env_node;

	env_node = l_env;
	while (env_node)
	{
		printf("%s=%s\n", ((t_env *)(env_node->content))->key,
			((t_env *)(env_node->content))->value);
		env_node = env_node->next;
	}
}

int
	ft_env(int argc, char **argv, t_list *env)
{
	(void)argc;
	(void)argv;
	print_env_list(env);
	return (0);
}
