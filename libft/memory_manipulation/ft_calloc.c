/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaliste <agaliste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 09:05:18 by agaliste          #+#    #+#             */
/*   Updated: 2022/01/24 12:12:20 by agaliste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void
	*ft_calloc(size_t count, size_t size)
{
	int		*obj;

	obj = malloc(size * count);
	if (obj == NULL)
		return (NULL);
	ft_bzero(obj, count * size);
	return (obj);
}
