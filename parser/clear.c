/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madorna- <madorna-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 23:14:57 by madorna-          #+#    #+#             */
/*   Updated: 2021/11/28 06:05:42 by madorna-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Normal text, no flags. Put in buffer normally
*/
int
	parse_clear(t_mini *mini)
{
	mini->flag += CLEAR;
	// printf("Called Clear function\n");
	return (0);
}
