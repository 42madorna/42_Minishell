/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madorna- <madorna-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 02:07:09 by madorna-          #+#    #+#             */
/*   Updated: 2022/02/11 19:54:53 by madorna-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char
	*ft_strjoin_env(const char *s1, const char *s2)
{
	char			*str;
	unsigned int	i;
	unsigned int	j;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	str = malloc((sizeof(char) * ft_strlen(s1) + ft_strlen(s2)) + 2);
	if (str == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
		str[j++] = s1[i++];
	str[j++] = '=';
	i = 0;
	while (s2[i])
		str[j++] = s2[i++];
	str[ft_strlen(s1) + ft_strlen(s2) + 1] = '\0';
	return (str);
}
