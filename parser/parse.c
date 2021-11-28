/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madorna- <madorna-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 00:43:51 by madorna-          #+#    #+#             */
/*   Updated: 2021/11/28 06:17:57 by madorna-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// char
// 	*ft_dollar(char **line)
// {
// 	char	*parsed;
// 	int		i;

// 	parsed = calloc(1, sizeof(char *));
// 	i = 0;
// 	++*line;
// 	while (**line && !ft_strncmp(*line, DQUOTE, 1))
// 	{
// 		parsed[i] = **line;
// 		++*line;
// 		++i;
// 	}
// 	return (getenv(parsed));
// }

// int
// 	find_quote(char **line, char *q)
// {
// 	++*line;
// 	// printf("current: %s\n", *line);
// 	while (*(*line))
// 	{
// 		// printf("current: %s\n", (*line));
// 		if (!ft_strncmp(q, DQUOTE, 1) && **line == '$')
// 			printf("%s\n", ft_dollar(line));
// 		if (!ft_strncmp(*line, q, 1))
// 			return (0);
// 		++*line;
// 	}
// 	return (1);
// }

int
	specials(t_mini *mini)
{
	// [MINS-50] HERE!
	// printf("received %s\n", mini->line_cpy);
	if (!ft_strncmp(mini->line_cpy, ">>", 2))
	{
		/*
		** ">> file"
		** Append opens the file in O_APPEND mode and uses it as STDOUT
		*/
		mini->line_cpy += 2;
		mini->p[APPEND](mini);
		// return (printf("Append!\n") - 8);
	}
	if (!ft_strncmp(mini->line_cpy, "<<", 2))
	{
		/*
		** DELIMITER should be like this "<< delim"
		** 	then, ">" is prompted and waits for "delim" to be written.
		** If there are many "<<", the "delim" has to be written in the order
		** 	the pipes have.
		*/
		mini->line_cpy += 2;
		mini->p[DELIMITER](mini);
		return (printf("DELIMITER!\n") - 12);
	}
	if (!ft_strncmp(mini->line_cpy, "<", 1))
	{
		/*
		** > Opens file in read mode and take it as STDIN
		** If file does not exist, bash prints this:
		** 	bash: noexiste: No existe el archivo o el directorio
		** IMPORTANT: In this case, a command is not required.
		*/
		// printf("In!\n");
		mini->line_cpy++;
		mini->p[IN](mini);
	}
	if (!ft_strncmp(mini->line_cpy, ">", 1))
	{
		/*
		** > Opens file in write mode and use it as STDOUT
		** If file does not exist, bash creates it.
		** IMPORTANT: In this case, a command is not required.
		*/
		// printf("Out!\n");
		mini->line_cpy++;
		mini->p[OUT](mini);
	}
	if (!ft_strncmp(mini->line_cpy, "|", 1))
	{
		/*
		** | Passes command[n] STDOUT to command[n + 1] STDIN
		** | can not be the first character at input. All commands/files
		** 	existence is checked before executing anything.
		*/
		printf("Pipe!\n");
		mini->line_cpy++;
		mini->p[PIPE](mini);
	}
	if (!ft_strncmp(mini->line_cpy, "\"", 1))
	{
		/*
		** " Ignores every special character except $, which would expand.
		** 	Also, the argv[n] should be saved ignoring espaces
		*/
		mini->line_cpy++;
		mini->p[DQUOTE](mini);
	}
	if (!ft_strncmp(mini->line_cpy, "'", 1))
	{
		/*
		** ' Ignores every special character.
		** 	Also, the argv[n] should be saved ignoring espaces
		*/
		mini->line_cpy++;
		mini->p[QUOTE](mini);
	}
	if (!ft_strncmp(mini->line_cpy, "$", 1))
	{
		/*
		** $ should expand the ENV_VAR name to its value.
		*/
		mini->line_cpy++;
		mini->p[DOLLAR](mini);
	}
	mini->p[CLEAR](mini);
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
	unexpected(t_mini *mini)
{
	const static char *tokens[] = {NULL, "|", ">", "'",
		"<<", "<", ">>", "$", "\""};

	return (printf("Unexpected token near `%s'\n", tokens[mini->flag]));
}

int
	parse(t_mini *mini)
{
	char	*str;
	t_cmd	cmd;
	int		i;

	mini->line_cpy = ft_strtrim(mini->line, " ");
	ft_bzero(&cmd, sizeof(t_cmd));
	cmd.env = mini->env;
	str = calloc(100, sizeof(char)); // TODO: Leak
	i = -1;
	if (*mini->line_cpy == '|')
		return (printf("Unexpected token near `|'\n"));
	while (*mini->line_cpy)
	{
		specials(mini);
		if (*mini->line_cpy == ' ' || *mini->line_cpy == '\t')
			ft_lstadd_back(&cmd.l_argv, ft_lstnew(mini->line_cpy)); // Leak
		str[++i] = *mini->line_cpy;
		mini->line_cpy++;
		/*
		** TODO: [MINS-63] Add parsed content to cmd.argv.
		** Example: echo "hola $HOME"
		** cmd.argv = {
		**     "echo",
		**     "hola /Users/madorna-"
		** }
		*/
	}
	printf("str is %s\n", str);
	// printf("flag is %d\n", mini->flag);
	// if (mini->flag > 0)
	// 	return (printf("Unexpected token\n"));
	if (mini->flag > 0)
		return (unexpected(mini));
	ft_lstadd_back(&cmd.l_argv, ft_lstnew(mini->line_cpy)); // TODO: Leaks
	// ft_lstiter(cmd.l_argv, print);
	// ft_execve(cmd);
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
