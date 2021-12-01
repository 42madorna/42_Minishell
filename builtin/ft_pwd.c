/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madorna- <madorna-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 16:48:23 by madorna-          #+#    #+#             */
/*   Updated: 2021/12/01 02:56:51 by madorna-         ###   ########.fr       */
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
	printf("%s\n", path);
	free(path);
	return (0);
}
