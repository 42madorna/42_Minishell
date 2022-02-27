/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaliste <agaliste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 00:53:12 by madorna-          #+#    #+#             */
/*   Updated: 2022/02/27 17:11:08 by agaliste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include "builtin.h"
# include "cleanup.h"
# include "command_split.h"
# define _GNU_SOURCE
# include <stdio.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <errno.h>
# include <sys/wait.h>
# include <dirent.h>

# define SHELL_NAME "putishell"

// # define PIPE "|"
// # define DQUOTE "\""
// # define QUOTE "\'"
// # define DOLLAR "$"
// # define DELIMITER "<<"
// # define IN "<"
// # define APPEND ">>"
// # define OUT ">"

# define CLEAR 0b00000000	 // 0
# define PIPE 0b00000001		 // 1
# define OUT 0b00000010		 // 2
# define DELIMITER 0b00000011 // 3
# define IN 0b00000100		 // 4
# define APPEND 0b00000101	 // 5
# define QUOTE 0b00000110	 // 6
# define DOLLAR 0b00000111	 // 7
# define DQUOTE 0b00001000	 // 8

# define READ_END 0
# define WRITE_END 1

/*
** General minishell struct
*/
typedef struct s_mini
{
	int		argc;
	char	**argv;
	char	**env;
	char	*line;
	char	*line_cpy;
	char	*buffer;
	int		flag;
	int		p_error;
	t_list	*l_env;
	t_list	*cmds;
	t_list	*delimiters;
	t_list	*chars;
	int		(*p[9])(struct s_mini *);
	int		ret;
	char	**env_cmd;
	int		parse_err;
	int		pipe_count;
	int		open_style;
}				t_mini;

/*
** Command structure (aka t_mini->cmds)
*/
typedef struct s_cmd
{
	int		argc;
	char	**argv;
	char	**env;
	t_list	*l_argv;
	int		infile;
	int		outfile;
	char	*path;
	pid_t	pid;
	int		num;
	int		notexists;
	int		builtin;
}				t_cmd;

/*
** Parser minishell struct (aka t_mini->chars)
*/
typedef struct s_chars
{
	char	c;
	int		flag;
	int		end;
}				t_chars;

/*
** Environment variables struct (aka t_mini->l_env)
*/
typedef struct s_env
{
	char	*key;
	char	*value;
	char	**split_mem;
}				t_env;

/*
** Command PIDs
*/
pid_t	g_pid[255];

/*
** Parser functions
*/
void	quote_finder(t_mini *mini);
void	dollar_finder(t_mini *mini);
int		parse(t_mini *mini);
int		specials(t_mini *mini);
int		parse_clear(t_mini *mini);
int		parse_pipe(t_mini *mini);
int		parse_dquote(t_mini *mini);
int		parse_quote(t_mini *mini);
int		parse_dollar(t_mini *mini);
int		parse_delimiter(t_mini *mini);
int		parse_in(t_mini *mini);
int		parse_append(t_mini *mini);
int		parse_out(t_mini *mini);

void	make_command(t_mini *mini);
void	make_argv(t_mini *mini);

char	*unclosed_name(int flag);
int		save_char(t_mini *mini, t_chars *chars);
void	ft_del_chars(void *chars);

void	flagger(t_mini *mini);
void	command_split(t_mini *mini);

/*
** Environment variables functions
*/
void	ft_env_to_lst(t_mini *mini);
char	*ft_env_value(t_list *l_env, const char *key);
void	ft_env_set_value(t_list *l_env, char *key, char *new_value);
void	make_env(t_mini *mini);
void	ft_free_env(void *env);

/*
** Pipex functions
*/
void	pipex(t_mini *mini);

/*
** Core loop
*/
void	mini_loop(t_mini *mini);
void	promt(t_mini *mini, int type);

void	ft_delim(t_mini *mini);

/*
** Init
*/
void	set_functions(t_mini *mini);

/*
** Exec functions
*/
int		ft_execve(t_cmd *command);
int		ft_search_cmd(t_list *l_env, t_cmd *cmd);
void	ft_check_command(t_mini *mini);
void	ft_check_existence(t_cmd *cmd, int saved_fd[2]);
void	close_dup(int saved_fd[2]);

/*
** Utils functions
*/
char	*ft_strjoin_path(const char *s1, const char *s2);
char	*ft_strjoin_env(const char *s1, const char *s2);

/*
** Export sort
*/
t_list	*ft_find_max(t_list *l_env);
int		cmp_env(t_env *a, t_env *b);
void	ft_lstsort(t_list *l_env);

/*
** Signals
*/
void	signal_q(int sig);

#endif