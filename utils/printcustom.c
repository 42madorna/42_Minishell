/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printcustom.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaliste <agaliste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 18:33:07 by agaliste          #+#    #+#             */
/*   Updated: 2022/03/02 18:47:23 by agaliste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void
	printcustom(char *s1, char *s2, int fd)
{
	char	*print;

	print = ft_strjoin(s1, s2);
	if (print)
	{
		ft_putstr_fd(print, fd);
		free(print);
	}
}
