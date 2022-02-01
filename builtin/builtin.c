/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madorna- <madorna-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 16:52:20 by madorna-          #+#    #+#             */
/*   Updated: 2022/02/01 20:06:30 by madorna-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "libft/libft.h"

int
	builtin(char **argv, struct s_mini *mini)
{
	t_cmd	*cmd;

	cmd = mini->cmds->content;
	if (!ft_strncmp(cmd->argv[0], "exit", ft_strlen(argv[0])))
		return (ft_exit(cmd->argc, cmd->argv, mini->l_env, mini));
	if (!ft_strncmp(cmd->argv[0], "pwd", ft_strlen(argv[0])))
		return (ft_pwd(cmd->argc, cmd->argv, mini->l_env));
	if (!ft_strncmp(cmd->argv[0], "cd", ft_strlen(argv[0])))
		return (ft_cd(cmd->argc, cmd->argv, mini->l_env));
	if (!ft_strncmp(cmd->argv[0], "echo", ft_strlen(argv[0])))
		return (ft_echo(cmd->argc, cmd->argv, mini->l_env));
	if (!ft_strncmp(cmd->argv[0], "env", ft_strlen(argv[0])))
		return (ft_env(cmd->argc, cmd->argv, mini->l_env));
	if (!ft_strncmp(cmd->argv[0], "unset", ft_strlen(argv[0])))
		return (ft_unset(cmd->argc, cmd->argv, mini->l_env));
	if (!ft_strncmp(cmd->argv[0], "export", ft_strlen(argv[0])))
		return (ft_export(cmd->argc, cmd->argv, mini->l_env));
	return (1);
}
