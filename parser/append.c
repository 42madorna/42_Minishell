/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madorna- <madorna-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 23:25:46 by madorna-          #+#    #+#             */
/*   Updated: 2021/11/28 06:05:51 by madorna-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** If there is no file after APPEND (>>), or file does not exist, error!
** Add last file to cmds->outfile and not to buffer.
** All the files have to be created it these don't exist!
*/
int
	parse_append(t_mini *mini)
{
	mini->flag += APPEND;
	// printf("APPEND received %s\n", mini->line_cpy);
	if ((mini->p_error = open(++mini->line_cpy, O_CREAT | O_WRONLY | O_APPEND)) == -1)
		printf(SHELL_NAME ": %s: %s\n", mini->line_cpy, strerror(errno));
	// printf("Called Append function\n");
	return (0);
}
