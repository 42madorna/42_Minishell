/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madorna- <madorna-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 00:53:12 by madorna-          #+#    #+#             */
/*   Updated: 2021/11/24 01:07:27 by madorna-         ###   ########.fr       */
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

#define SHELL_NAME "minishell$ "

# define PIPE '|'
# define DQUOTE '"'
# define QUOTE '\''
# define DOLLAR '$'
# define IN '<'
# define OUT '>'

typedef struct	s_mini
{
	int		argc;
	char	**argv;
	char	**env;
	char	*line;
	int		errno;
	t_list	*l_env;
	t_list	*cmds;
}				t_mini;

typedef struct	s_cmd
{
	int		argc;
	char	**argv;
	char	**env;
	char	*infile;
	char	*outfile;
}				t_cmd;

/*
** Parser functions
*/
void	parse(t_mini *mini);

/*
** Exec functions
*/
int		ft_execve(t_cmd command);

#endif