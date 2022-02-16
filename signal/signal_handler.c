/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madorna- <madorna-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 07:28:02 by madorna-          #+#    #+#             */
/*   Updated: 2022/02/16 07:28:13 by madorna-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void
	signal_q(int sig)
{
	int	i;

	i = 0;
	while (g_pid[i])
	{
		kill(g_pid[i], sig);
		g_pid[i++] = 0;
	}
	if (sig == 3)
		printf("Quit: %d\n", sig);
	else
		printf("\n");
}
