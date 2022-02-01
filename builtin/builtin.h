/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madorna- <madorna-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 16:53:49 by madorna-          #+#    #+#             */
/*   Updated: 2022/02/01 20:06:09 by madorna-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H
# include "minishell.h"

struct	s_mini;

int	builtin(char **argv, struct s_mini *mini);
int	ft_pwd(int argc, char **argv, t_list *env);
int	ft_exit(int argc, char **argv, t_list *env, struct s_mini *mini);
int	ft_cd(int argc, char **argv, t_list *env);
int	ft_env(int argc, char **argv, t_list *env);
int	ft_unset(int argc, char **argv, t_list *env);
int	ft_export(int argc, char **argv, t_list *env);
int	ft_echo(int argc, char **argv, t_list *l_env);

#endif