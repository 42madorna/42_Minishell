/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaliste <agaliste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/24 20:58:38 by agaliste          #+#    #+#             */
/*   Updated: 2021/09/20 19:50:32 by agaliste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned int	i;

	i = 0;
	if (!dst && !src)
		return (NULL);
	if (src > dst)
	{
		while (i < len)
		{
			((char *)dst)[i] = ((char *)dst)[i];
			i++;
		}
	}
	else
	{
		i = len;
		while (i-- > 0)
			((char *)dst)[i] = ((char *)dst)[i];
	}
	return (dst);
}
