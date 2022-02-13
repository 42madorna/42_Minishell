/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_search_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madorna- <madorna-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 00:46:27 by madorna-          #+#    #+#             */
/*   Updated: 2022/02/13 05:53:38 by madorna-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

inline static int
	check_route(t_cmd *cmd, int *fd)
{
	DIR		*dir;

	if (ft_strchr(cmd->argv[0], '/'))
	{
		dir = opendir(cmd->argv[0]);
		if (dir)
		{
			closedir(dir);
			return (2);
		}
		*fd = open(cmd->argv[0], O_RDONLY);
		if (*fd >= 0)
		{
			cmd->path = ft_strdup(cmd->argv[0]);
			close(*fd);
			return (0);
		}
		return (1);
	}
	return (3);
}

inline static int
	check_name(char **env, t_cmd *cmd, int *fd)
{
	int		i;
	char	*path;

	i = 0;
	while (env[i])
	{
		path = ft_strjoin_path(env[i++], cmd->argv[0]);
		*fd = open(path, O_RDONLY);
		if (*fd >= 0)
		{
			cmd->path = path;
			ft_free_tab(env);
			close(*fd);
			return (0);
		}
		close(*fd);
		free(path);
	}
	ft_free_tab(env);
	return (1);
}

int
	ft_search_cmd(t_list *l_env, t_cmd *cmd)
{
	char	**env;
	char	*path_val;
	int		fd;
	int		ret;

	ret = check_route(cmd, &fd);
	if (ret != 3)
		return (ret);
	path_val = ft_env_value(l_env, "PATH");
	env = ft_split(path_val, ':');
	free(path_val);
	if (!env)
		return (1);
	return (check_name(env, cmd, &fd));
}
