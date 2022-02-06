/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_search_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madorna- <madorna-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 00:46:27 by madorna-          #+#    #+#             */
/*   Updated: 2022/02/06 05:19:36 by madorna-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int
	ft_search_cmd(t_list *l_env, t_cmd *cmd)
{
	char	**env;
	char	*path;

	if (ft_strchr(cmd->argv[0], '/'))
	{
		if (open(cmd->argv[0], O_RDONLY) >= 0)
		{
			cmd->path = cmd->argv[0];
			return (0);
		}
		else
			return (1);
	}
	env = ft_split(ft_env_value(l_env, "PATH"), ':');
	if (!env)
		return (1);
	for (int i = 0; env[i]; i++)
	{
		path = ft_strjoin_path(env[i], cmd->argv[0]);
		// printf("Trying '%s'\n", path);
		if (open(path, O_RDONLY) >= 0)
		{
			cmd->path = path;
			free(env);
			return (0);
		}
		free(path);
	}
	free(env);
	return (1);
}
