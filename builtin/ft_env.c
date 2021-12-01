/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madorna- <madorna-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 05:13:01 by madorna-          #+#    #+#             */
/*   Updated: 2021/12/01 02:06:11 by madorna-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** builtin: env
** env -> print environment variables
** Keep in mind that env is not meant to take arguments
** 	or optins as the subject says !
*/

int
	ft_env(int argc, char **argv, t_list *env)
{
	(void)argc;
	(void)argv;
	write(1, "\n", 1);
	// print_env_list(env, __FUNCTION__);
	return (0);
}
