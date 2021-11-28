/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madorna- <madorna-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 23:25:46 by madorna-          #+#    #+#             */
/*   Updated: 2021/11/28 06:06:00 by madorna-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** If there is no file after IN (<), or file does not exist, error!
** Add last file to cmds->infile and not to buffer.
*/
int
	parse_in(t_mini *mini)
{
	mini->flag += IN;
	// printf("IN received %s\n", mini->line_cpy);
	if ((mini->p_error = open(++mini->line_cpy, O_RDONLY)) == -1)
		printf(SHELL_NAME ": %s: %s\n", mini->line_cpy, strerror(errno));
	// printf("Called In function\n");
	return (0);
}
