/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madorna- <madorna-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 00:53:12 by madorna-          #+#    #+#             */
/*   Updated: 2021/11/23 23:48:50 by madorna-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include "builtin.h"
# define  _GNU_SOURCE
# include <stdio.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>

#define SHELL_NAME "minishell"


typedef struct	s_mini
{
	int		argc;
	char	**argv;
	char	**env;
	char	*line;
	t_list	*l_env;
}				t_mini;

#endif