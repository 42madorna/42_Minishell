/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaliste <agaliste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 18:01:57 by agaliste          #+#    #+#             */
/*   Updated: 2022/03/02 18:08:07 by agaliste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "minishell.h"

struct	s_cmd;

void	close_dup(int saved_fd[2]);
void	ft_in_out(int in, int out, int saved_fd[2], struct s_cmd *cmd);
void	ft_init_pipex(int *in_fd, int pipes[2]);

#endif