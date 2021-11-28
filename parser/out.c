/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   out.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madorna- <madorna-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 23:25:46 by madorna-          #+#    #+#             */
/*   Updated: 2021/11/28 06:06:05 by madorna-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** If there is no file after OUT (>), or file does not exist, error!
** Add last file to cmds->outfile and not to buffer.
** All the files have to be created it these don't exist!
*/
int
	parse_out(t_mini *mini)
{
	mini->flag += OUT;
	// printf("OUT received %s\n", mini->line_cpy);
	if ((mini->p_error = open(++mini->line_cpy, O_CREAT | O_WRONLY)) == -1)
		printf(SHELL_NAME ": %s: %s\n", mini->line_cpy, strerror(errno));
	// printf("Called Out function\n");
	return (0);
}
