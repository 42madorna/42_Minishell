/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaliste <agaliste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/24 21:06:15 by agaliste          #+#    #+#             */
/*   Updated: 2021/03/11 13:57:38 by agaliste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	i;
	char	*src;

	i = 0;
	src = (char *)s;
	while (*src != c && i < n)
	{
		if (*src == '\0')
			return (NULL);
		src++;
		i++;
	}
	if (i == n)
		return (NULL);
	else
		return (src);
}
