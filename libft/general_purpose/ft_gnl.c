/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gnl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaliste <agaliste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/13 23:37:11 by agaliste          #+#    #+#             */
/*   Updated: 2022/01/15 15:04:33 by agaliste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static inline void
	*freeline(char *line)
{
	free(line);
	return (NULL);
}

static inline int
	check_buffer(char *pos, char **line)
{
	char	*aux;
	char	*otro;
	char	aux2[BUFFER_SIZE + 1];

	aux = ft_strchr(pos, '\n');
	otro = *line;
	if (aux)
	{
		ft_bzero(aux2, BUFFER_SIZE + 1);
		*aux = '\0';
		*line = ft_strjoin(otro, pos);
		free(otro);
		ft_memcpy(aux2, aux + 1, ft_strlen(aux + 1));
		ft_bzero(pos, BUFFER_SIZE + 1);
		ft_memcpy(pos, aux2, ft_strlen(aux2));
		otro = *line;
		*line = ft_strjoin(otro, "\n");
		free(otro);
		return (1);
	}
	*line = ft_strjoin(otro, pos);
	free(otro);
	ft_bzero(pos, BUFFER_SIZE + 1);
	return (0);
}

char
	*ft_gnl(int fd)
{
	char		*line;
	static char	pos[BUFFER_SIZE + 1];
	int			rd;

	line = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (fd < 0 || fd > 256 || BUFFER_SIZE <= 0 || !line)
		return (freeline(line));
	ft_bzero(line, BUFFER_SIZE + 1);
	if (check_buffer(pos, &line))
		return (line);
	rd = read(fd, pos, BUFFER_SIZE);
	while (rd && rd != -1)
	{
		if (check_buffer(pos, &line))
			return (line);
		rd = read(fd, pos, BUFFER_SIZE);
	}
	if (line[0] == '\0')
		return (freeline(line));
	return (line);
}
