/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adorna_r <adorna_r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 00:43:51 by madorna-          #+#    #+#             */
/*   Updated: 2022/01/31 00:35:13 by adorna_r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int
// 	specials(t_mini *mini)
// {
// 	// [MINS-50] HERE!
// 	// printf("received %s\n", mini->line_cpy);
// 	if (!ft_strncmp(mini->line_cpy, ">>", 2))
// 	{
// 		/*
// 		** ">> file"
// 		** Append opens the file in O_APPEND mode and uses it as STDOUT
// 		*/
// 		mini->line_cpy += 2;
// 		return (mini->p[APPEND);
// 		// return (printf("Append!\n") - 8);
// 	}
// 	if (!ft_strncmp(mini->line_cpy, "<<", 2))
// 	{
// 		/*
// 		** DELIMITER should be like this "<< delim"
// 		** 	then, ">" is prompted and waits for "delim" to be written.
// 		** If there are many "<<", the "delim" has to be written in the order
// 		** 	the pipes have.
// 		*/
// 		mini->line_cpy += 2;
// 		return (mini->p[DELIMITER](mini));
// 		return (printf("DELIMITER!\n") - 12);
// 	}
// 	if (!ft_strncmp(mini->line_cpy, "<", 1))
// 	{
// 		/*
// 		** > Opens file in read mode and take it as STDIN
// 		** If file does not exist, bash prints this:
// 		** 	bash: noexiste: No existe el archivo o el directorio
// 		** IMPORTANT: In this case, a command is not required.
// 		*/
// 		// printf("In!\n");
// 		mini->line_cpy++;
// 		return (mini->p[IN](mini));
// 	}
// 	if (!ft_strncmp(mini->line_cpy, ">", 1))
// 	{
// 		/*
// 		** > Opens file in write mode and use it as STDOUT
// 		** If file does not exist, bash creates it.
// 		** IMPORTANT: In this case, a command is not required.
// 		*/
// 		// printf("Out!\n");
// 		mini->line_cpy++;
// 		return (mini->p[OUT](mini));
// 	}
// 	if (!ft_strncmp(mini->line_cpy, "|", 1))
// 	{
// 		/*
// 		** | Passes command[n] STDOUT to command[n + 1] STDIN
// 		** | can not be the first character at input. All commands/files
// 		** 	existence is checked before executing anything.
// 		*/
// 		printf("Pipe!\n");
// 		mini->line_cpy++;
// 		return (mini->p[PIPE](mini));
// 	}
// 	if (!ft_strncmp(mini->line_cpy, "\"", 1))
// 	{
// 		/*
// 		** " Ignores every special character except $, which would expand.
// 		** 	Also, the argv[n] should be saved ignoring espaces
// 		*/
// 		mini->line_cpy++;
// 		return (mini->p[DQUOTE](mini));
// 	}
// 	if (!ft_strncmp(mini->line_cpy, "'", 1))
// 	{
// 		/*
// 		** ' Ignores every special character.
// 		** 	Also, the argv[n] should be saved ignoring espaces
// 		*/
// 		mini->line_cpy++;
// 		return (mini->p[QUOTE](mini));
// 	}
// 	if (!ft_strncmp(mini->line_cpy, "$", 1))
// 	{
// 		/*
// 		** $ should expand the ENV_VAR name to its value.
// 		*/
// 		mini->line_cpy++;
// 		return (mini->p[DOLLAR](mini));
// 	}
// 	mini->p[CLEAR](mini);
// 	mini->line_cpy++;
// 	return (0);
// }

// void
// 	print(void *lst)
// {
// 	char *str;

// 	str = lst;
// 	printf("node content '%s'\n", str);
// }

// int
// 	unexpected(t_mini *mini)
// {
// 	const static char *tokens[] = {NULL, "|", ">", "'",
// 		"<<", "<", ">>", "$", "\""};

// 	return (printf("Unexpected token near `%s'\n", tokens[mini->flag]));
// }

// int
// 	parse(t_mini *mini)
// {
// 	t_cmd	cmd;
// 	int		i;

// 	mini->line_cpy = ft_strtrim(mini->line, " ");
// 	ft_bzero(&cmd, sizeof(t_cmd));
// 	cmd.env = mini->env;
// 	mini->buffer = calloc(1024, ft_strlen(mini->line_cpy)); // TODO: Leak
// 	i = -1;
// 	if (*mini->line_cpy == '|')
// 		return (printf("Unexpected token near `|'\n"));
// 	while (*mini->line_cpy)
// 	{
// 		specials(mini);
// 		if (*mini->line_cpy == ' ' || *mini->line_cpy == '\t')
// 			ft_lstadd_back(&cmd.l_argv, ft_lstnew(mini->line_cpy)); // Leak
// 		// mini->line_cpy++;
// 		/*
// 		** TODO: [MINS-63] Add parsed content to cmd.argv.
// 		** Example: echo "hola $HOME"
// 		** cmd.argv = {
// 		**     "echo",
// 		**     "hola /Users/madorna-"
// 		** }
// 		*/
// 	}
// 	printf("str is %s\n", mini->buffer);
// 	// printf("flag is %d\n", mini->flag);
// 	// if (mini->flag > 0)
// 	// 	return (printf("Unexpected token\n"));
// 	if (mini->flag > 0)
// 		return (unexpected(mini));
// 	ft_lstadd_back(&cmd.l_argv, ft_lstnew(mini->line_cpy)); // TODO: Leaks
// 	// ft_lstiter(cmd.l_argv, print);
// 	// ft_execve(cmd);
// 	// execve(cmd.argv[0], cmd.argv, mini->env);
// 	// while (*line)
// 	// {
// 	// 	if (!strcmp(line, "exit"))
// 	// 	{
// 	// 		mini->argv[0] = strdup("exit\0");
// 	// 		builtin(mini->argv, mini);
// 	// 	}
// 	// 	write(1, line, 1);
// 	// 	++line;
// 	// }
// 	return (0);
// }

// FIXME: QUOTE flag should prevent pointer move
int
	specials(t_mini *mini)
{
	if (!ft_strncmp(mini->line_cpy, ">>", 2))
		/*
		** ">> file"
		** Append opens the file in O_APPEND mode and uses it as STDOUT
		*/
		mini->p[APPEND](mini);
	if (!ft_strncmp(mini->line_cpy, "<<", 2))
		/*
		** DELIMITER should be like this "<< delim"
		** 	then, ">" is prompted and waits for "delim" to be written.
		** If there are many "<<", the "delim" has to be written in the order
		** 	the pipes have.
		*/
		mini->p[DELIMITER](mini);
	if (!ft_strncmp(mini->line_cpy, "<", 1))
		/*
		** > Opens file in read mode and take it as STDIN
		** If file does not exist, bash prints this:
		** 	bash: noexiste: No existe el archivo o el directorio
		** IMPORTANT: In this case, a command is not required.
		*/
		// printf("In!\n");
		mini->p[IN](mini);
	if (!ft_strncmp(mini->line_cpy, ">", 1))
		/*
		** > Opens file in write mode and use it as STDOUT
		** If file does not exist, bash creates it.
		** IMPORTANT: In this case, a command is not required.
		*/
		// printf("Out!\n");
		mini->p[OUT](mini);
	if (!ft_strncmp(mini->line_cpy, "|", 1))
		/*
		** | Passes command[n] STDOUT to command[n + 1] STDIN
		** | can not be the first character at input. All commands/files
		** 	existence is checked before executing anything.
		*/
		mini->p[PIPE](mini);
	if (!ft_strncmp(mini->line_cpy, "\"", 1))
		/*
		** " Ignores every special character except $, which would expand.
		** 	Also, the argv[n] should be saved ignoring espaces
		*/
		mini->p[DQUOTE](mini);
	if (!ft_strncmp(mini->line_cpy, "'", 1))
		/*
		** ' Ignores every special character.
		** 	Also, the argv[n] should be saved ignoring espaces
		*/
		mini->p[QUOTE](mini);
	if (!ft_strncmp(mini->line_cpy, "$", 1))
		/*
		** $ should expand the ENV_VAR name to its value.
		*/
		mini->p[DOLLAR](mini);
	if (!ft_strncmp(mini->line_cpy, ">", 1))
		/*
		** > Opens file in write mode and use it as STDOUT
		** If file does not exist, bash creates it.
		** IMPORTANT: In this case, a command is not required.
		*/
		// printf("Out!\n");
		mini->p[OUT](mini);
	return (mini->flag);
}

void
	print(void *lst)
{
	t_chars *chars;

	chars = lst;
	printf("node content '%c%c', flag '%d'\n", chars->c == 0 ? '\\' : chars->c, chars->c == 0 ? '0' : '\0' , chars->flag);
}

int
	parse(t_mini *mini)
{
	t_chars	*chars;
	char	*p;

	mini->line_cpy = ft_strtrim(mini->line, " "); // TODO: Leak
	p = mini->line_cpy;
	while (*mini->line_cpy)
	{
		mini->p[CLEAR](mini);
		chars = calloc(1, sizeof(t_chars*));
		chars->flag = specials(mini);
		if (!*mini->line_cpy)
		{
			free(chars);
			break ;
		}
		if (*mini->line_cpy == '|')
			chars->flag = PIPE;
		chars->c = *mini->line_cpy;
		ft_lstadd_back(&mini->chars, ft_lstnew(chars));
		mini->line_cpy++;
	}
	// FIXME: FLAGS NOT CLOSING
	// if (chars->flag != 0 && chars->flag != DOLLAR)
	// {
	// 	printf("Expected token before \\0\n");
	// 	return (1);
	// 	// TODO: Free...
	// }
	chars = calloc(1, sizeof(t_chars*));
	chars->flag = 0;
	chars->c = '\0';
	ft_lstadd_back(&mini->chars, ft_lstnew(chars));
	free(p);
	// Uncomment this to see what does mini->chars have
	// ft_lstiter(mini->chars, print);
	make_command(mini);
	ft_lstclear(&mini->chars, free);
	return (0);
}