/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madorna- <madorna-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 00:43:51 by madorna-          #+#    #+#             */
/*   Updated: 2021/11/24 03:21:56 by madorna-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char
	*ft_dollar(char **line)
{
	char	*parsed;
	int		i;

	parsed = calloc(1, sizeof(char *));
	i = 0;
	++*line;
	while (**line && **line != DQUOTE)
	{
		parsed[i] = **line;
		++*line;
		++i;
	}
	return (getenv(parsed));
}

int
	find_quote(char **line, char q)
{
	++*line;
	// printf("current: %s\n", *line);
	while (*(*line))
	{
		// printf("current: %s\n", (*line));
		if (q == DQUOTE && **line == '$')
			printf("%s\n", ft_dollar(line));
		if (**line == q)
			return (0);
		++*line;
	}
	return (1);
}

int
	specials(char **line)
{
	// printf("received %s\n", *line);
	if (*(*line) == PIPE)
		return (0);
	if (*(*line) == DQUOTE)
		return (find_quote(line, DQUOTE));
	if (*(*line) == QUOTE)
		return (find_quote(line, QUOTE));
	if (*(*line) == DOLLAR)
		printf("%s\n", ft_dollar(line));
	if (*(*line) == IN)
		return (0);
	if (*(*line) == OUT)
		return (0);
	return (0);
}

void
	print(void *lst)
{
	char *str;

	str = lst;
	printf("node content '%s'\n", str);
}

int
	parse(t_mini *mini)
{
	char	*line;
	char	*str;
	t_cmd	cmd;
	int		i;

	line = mini->line;
	ft_bzero(&cmd, sizeof(t_cmd));
	cmd.env = mini->env;
	str = malloc(sizeof(char *));
	i = -1;
	while (*line)
	{
		if (specials(&line))
			return (printf("Unexpected token\n"));
		if (*line == ' ' || *line == '\t')
			ft_lstadd_back(&cmd.l_argv, ft_lstnew(++line));
		str[++i] = *line;
		line++;
		/*
		** TODO: [MINS-63] Add parsed content to cmd.argv.
		** Example: echo "hola $HOME"
		** cmd.argv = {
		**     "echo",
		**     "hola /Users/madorna-"
		** }
		*/
	}
	ft_lstadd_back(&cmd.l_argv, ft_lstnew(line));
	ft_lstiter(cmd.l_argv, print);
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
	return (0);
}
