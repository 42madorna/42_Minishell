/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaliste <agaliste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 17:33:08 by agaliste          #+#    #+#             */
/*   Updated: 2021/03/11 13:57:07 by agaliste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int n)
{
	char	*ret;
	char	*null;

	ret = (char *)s;
	null = (char *) NULL;
	if (ft_strchr(ret, n) == null)
		return (NULL);
	while (*ret != '\0')
		ret++;
	while (*ret != n)
		ret--;
	return (ret);
}
