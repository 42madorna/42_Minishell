/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madorna- <madorna-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 00:43:51 by madorna-          #+#    #+#             */
/*   Updated: 2021/11/24 00:51:47 by madorna-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int
	specials(char *line)
{
	if (*line == PIPE)
		return (*line);
	if (*line == DQUOTE)
		return (*line);
	if (*line == QUOTE)
		return (*line);
	if (*line == DOLLAR)
		return (*line);
	if (*line == IN)
		return (*line);
	if (*line == OUT)
		return (*line);
	return (0);
}

void
	parse(t_mini *mini)
{
	char	*line;
	t_cmd	cmd;

	line = mini->line;
	ft_bzero(&cmd, sizeof(t_cmd));
	cmd.argv = ft_split(line, ' ');
	while (*line)
	{
		if (specials(line) != 0)
			printf("Special char detected\n");
		line++;
	}
	ft_execve(cmd);
	// execve(cmd.argv[0], cmd.argv, mini->env);
	// while (*line)
	// {
	// 	if (!strcmp(line, "exit"))
	// 	{
	// 		mini->argv[0] = strdup("exit\0");
	// 		builtin(mini->argv, mini);
	// 	}
	// 	write(1, line, 1);
	// 	++line;
	// }
}
