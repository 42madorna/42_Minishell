/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_search_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madorna- <madorna-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 00:46:27 by madorna-          #+#    #+#             */
/*   Updated: 2022/01/31 05:11:48 by madorna-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int
	ft_search_cmd(t_list *l_env, t_cmd *cmd)
{
	char	**env;
	char	*path;

	env = ft_split(ft_env_value(l_env, "PATH"), ':');
	for (int i = 0; env[i]; i++)
	{
		// FIXME: MINS-81
		path = ft_strjoin(env[i], cmd->argv[0]); // TODO: Leaks
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
