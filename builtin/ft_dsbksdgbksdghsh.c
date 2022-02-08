/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dsbksdgbksdghsh.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madorna- <madorna-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 05:21:24 by madorna-          #+#    #+#             */
/*   Updated: 2022/02/08 06:00:09 by madorna-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int
	ft_dsbksdgbksdghsh(void)
{
	ft_putstr_fd(SHELL_NAME, STDERR_FILENO);
	ft_putstr_fd(": dsbksdgbksdghsh: command found. I mean, not found\n",
		STDERR_FILENO);
	return (0);
}
