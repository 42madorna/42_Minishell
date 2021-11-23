/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaliste <agaliste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 12:23:18 by agaliste          #+#    #+#             */
/*   Updated: 2021/03/11 13:40:39 by agaliste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	int	i;
	int	len;

	i = 0;
	if (!s || !fd)
		return ;
	len = ft_strlen(s);
	while (i < len)
	{
		ft_putchar_fd(s[i], fd);
		i++;
	}
}
