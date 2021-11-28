/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madorna- <madorna-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 16:48:23 by madorna-          #+#    #+#             */
/*   Updated: 2021/07/11 06:32:55 by madorna-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** builtin: pwd
** pwd takes current workdir using getcwd and prints it
** Please keep in mind that pwd does not have to manage options as the subject
** 	says !
*/

int
	ft_pwd(int argc, char **argv, t_list *env)
{
	char	*path;

	(void)env;
	(void)argc;
	(void)argv;
	path = NULL;
	path = getcwd(path, 0);
	write(1, "\n", 1);
	ft_putstr_fd(path, 1);
	write(1, "\n", 1);
	free(path);
	return (0);
}
