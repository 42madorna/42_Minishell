/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madorna- <madorna-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/11 04:06:40 by madorna-          #+#    #+#             */
/*   Updated: 2021/12/01 02:09:26 by madorna-         ###   ########.fr       */
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

int
	ft_unset(int argc, char **argv, t_list *env)
{
	write(1, "\n", 1);
	// if (argc >= 2)
	// 	del_env_vble(env, argv[1]);
	return (0);
}
