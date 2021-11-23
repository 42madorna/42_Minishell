/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaliste <agaliste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 21:06:01 by agaliste          #+#    #+#             */
/*   Updated: 2021/03/11 14:03:36 by agaliste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int					is_neg;
	unsigned int		nb;

	nb = 0;
	is_neg = 1;
	while (*str == '\f' || *str == '\n' || *str == '\r'
		|| *str == '\t' || *str == '\v' || *str == ' ')
		str++;
	if (*str == '+' || *str == '-')
		if (*str++ == '-')
			is_neg *= -1;
	while (*str >= '0' && *str <= '9')
	{
		nb = (nb * 10) + (*str - '0');
		str++;
	}
	return (nb * is_neg);
}
