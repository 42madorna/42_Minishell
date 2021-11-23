/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madorna- <madorna-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 16:53:49 by madorna-          #+#    #+#             */
/*   Updated: 2021/07/11 06:30:28 by madorna-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H
# include "minishell.h"

int	builtin(t_minishell *mini);
int	ft_pwd(t_list *env);
int	ft_exit(int status);
int	ft_cd(char *path, t_list *env);
int	ft_env(int argc, char **argv, t_list *env);
int	ft_unset(int argc, char **argv, t_list *env);
int	ft_export(int argc, char **argv, t_list *env);

#endif