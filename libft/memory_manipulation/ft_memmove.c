/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaliste <agaliste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/24 20:58:38 by agaliste          #+#    #+#             */
/*   Updated: 2022/02/13 17:17:59 by agaliste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void
	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t		i;
	const char	*src_cpy;
	char		*dst_cpy;

	src_cpy = (char *)src;
	dst_cpy = (char *)dst;
	i = 0;
	if (!dst && !src)
		return (NULL);
	if (src_cpy < dst_cpy)
	{
		while (++i <= len)
			dst_cpy[len - i] = (char)src_cpy[len - i];
	}
	else
		while (len-- > 0)
			*(dst_cpy++) = *(src_cpy++);
	return (dst);
}
