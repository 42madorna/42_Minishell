/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaliste <agaliste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 13:27:20 by agaliste          #+#    #+#             */
/*   Updated: 2021/02/04 16:40:47 by agaliste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	d;
	size_t	dst_size;

	dst_size = ft_strlen(dst);
	if (size <= ft_strlen(dst))
		return (size + ft_strlen(src));
	d = 0;
	while (src[d] != '\0' && dst_size + 1 < size)
	{
		dst[dst_size] = src[d];
		dst_size++;
		d++;
	}
	dst[dst_size] = '\0';
	return (ft_strlen(dst) + ft_strlen(&src[d]));
}
