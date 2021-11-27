/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madorna- <madorna-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 00:43:51 by madorna-          #+#    #+#             */
/*   Updated: 2021/11/27 04:48:18 by madorna-         ###   ########.fr       */
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
	while (**line && !ft_strncmp(*line, DQUOTE, 1))
	{
		parsed[i] = **line;
		++*line;
		++i;
	}
	return (getenv(parsed));
}

int
	find_quote(char **line, char *q)
{
	++*line;
	// printf("current: %s\n", *line);
	while (*(*line))
	{
		// printf("current: %s\n", (*line));
		if (!ft_strncmp(q, DQUOTE, 1) && **line == '$')
			printf("%s\n", ft_dollar(line));
		if (!ft_strncmp(*line, q, 1))
			return (0);
		++*line;
	}
	return (1);
}

int
	specials(char **line)
{
	// [MINS-50] HERE!
	// printf("received %s\n", *line);
	if (!ft_strncmp(*line, APPEND, 2))
	{
		/*
		** ">> file"
		** Append opens the file in O_APPEND mode and uses it as STDOUT
		*/
		*line += 2;
		return (printf("Append!\n") - 8);
	}
	if (!ft_strncmp(*line, DELIMITTER, 2))
	{
		/*
		** Delimitter should be like this "<< delim"
		** 	then, ">" is prompted and waits for "delim" to be written.
		** If there are many "<<", the "delim" has to be written in the order
		** 	the pipes have.
		*/
		*line += 2;
		return (printf("Delimitter!\n") - 12);
	}
	if (!ft_strncmp(*line, IN, 1))
		/*
		** > Opens file in read mode and take it as STDIN
		** If file does not exist, bash prints this:
		** 	bash: noexiste: No existe el archivo o el directorio
		** IMPORTANT: In this case, a command is not required.
		*/
		printf("In!\n");
	if (!ft_strncmp(*line, OUT, 1))
		/*
		** > Opens file in write mode and use it as STDOUT
		** If file does not exist, bash creates it.
		** IMPORTANT: In this case, a command is not required.
		*/
		printf("Out!\n");
	if (!ft_strncmp(*line, PIPE, 1))
		/*
		** | Passes command[n] STDOUT to command[n + 1] STDIN
		** | can not be the first character at input. All commands/files
		** 	existence is checked before executing anything.
		*/
		printf("Pipe!\n");
	if (!ft_strncmp(*line, DQUOTE, 1))
		/*
		** " Ignores every special character except $, which would expand.
		** 	Also, the argv[n] should be saved ignoring espaces
		*/
		return (find_quote(line, DQUOTE));
	if (!ft_strncmp(*line, QUOTE, 1))
		/*
		** ' Ignores every special character.
		** 	Also, the argv[n] should be saved ignoring espaces
		*/
		return (find_quote(line, QUOTE));
	if (!ft_strncmp(*line, DOLLAR, 1))
		/*
		** $ should expand the ENV_VAR name to its value.
		*/
		printf("%s\n", ft_dollar(line));
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
	str = malloc(sizeof(char *)); // TODO: Leak
	i = -1;
	while (*line)
	{
		if (specials(&line))
			return (printf("Unexpected token\n"));
		if (*line == ' ' || *line == '\t')
			ft_lstadd_back(&cmd.l_argv, ft_lstnew(++line)); // Leak
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
	ft_lstadd_back(&cmd.l_argv, ft_lstnew(line)); // TODO: Leaks
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
