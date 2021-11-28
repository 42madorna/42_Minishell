/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madorna- <madorna-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 23:18:31 by madorna-          #+#    #+#             */
/*   Updated: 2021/11/28 05:17:36 by madorna-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** If there isn't command[0], error!
** Add command to new (t_list*)mini->cmds node with t_cmd content
*/
int
	parse_pipe(t_mini *mini)
{
	mini->flag += PIPE;
	printf("Called Pipe function\n");
	return (0);
}
