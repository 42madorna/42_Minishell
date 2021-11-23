/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaliste <agaliste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 17:28:19 by agaliste          #+#    #+#             */
/*   Updated: 2021/09/20 19:46:49 by agaliste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_intlen(long nb)
{
	unsigned int	len;
	int				b;

	if (nb < 0)
		len = 2;
	else
		len = 1;
	b = nb / 10;
	while (b)
	{
		b /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		size;
	int		nb;

	size = ft_intlen(n);
	str = (char *)malloc(sizeof(char) * size + 1);
	if (str == NULL)
		return (NULL);
	nb = n;
	str[size] = '\0';
	while (size-- > 0)
	{
		if (nb < 0)
			str[size] = -(nb % 10) + '0';
		else
			str[size] = nb % 10 + '0';
		nb /= 10;
	}
	if (n < 0)
		str[0] = '-';
	return (str);
}
