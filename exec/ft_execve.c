/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madorna- <madorna-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 00:25:30 by madorna-          #+#    #+#             */
/*   Updated: 2022/02/11 19:39:21 by madorna-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int
	ft_execve(t_cmd *cmd)
{
	if (execve(cmd->path, cmd->argv, cmd->env) != 0)
		perror(strerror(errno));
	return (0);
}
