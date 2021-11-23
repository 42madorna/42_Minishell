/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaliste <agaliste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 13:47:37 by agaliste          #+#    #+#             */
/*   Updated: 2021/09/20 19:36:04 by agaliste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int n)
{
	char	*ret;

	if (!s)
		return (NULL);
	ret = (char *)s;
	while (*ret != n)
	{
		if (*ret == '\0')
			return (NULL);
		ret++;
	}
	return (ret);
}
