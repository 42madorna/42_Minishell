/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_search_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madorna- <madorna-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 00:46:27 by madorna-          #+#    #+#             */
/*   Updated: 2022/02/11 06:59:47 by madorna-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int
	ft_search_cmd(t_list *l_env, t_cmd *cmd)
{
	char	**env;
	char	*path;
	char	*path_env;
	int		fd;
	DIR		*dir;

	if (ft_strchr(cmd->argv[0], '/'))
	{
		dir = opendir(cmd->argv[0]);
		if (dir)
			return (2);
		fd = open(cmd->argv[0], O_RDONLY);
		if (fd >= 0)
		{
			cmd->path = cmd->argv[0];
			close(fd);
			return (0);
		}
		return (1);
	}
	path_env = ft_env_value(l_env, "PATH");
	env = ft_split(path_env, ':'); // TODO: Leaks?
	free(path_env);
	if (!env)
		return (1);
	for (int i = 0; env[i]; i++)
	{
		path = ft_strjoin_path(env[i], cmd->argv[0]);
		fd = open(path, O_RDONLY);
		if (fd >= 0)
		{
			cmd->path = path;
			free(env);
			close(fd);
			return (0);
		}
		close(fd);
		free(path);
	}
	free(env);
	return (1);
}
