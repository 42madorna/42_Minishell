/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madorna- <madorna-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 10:46:53 by pcosta-j          #+#    #+#             */
/*   Updated: 2021/08/01 12:22:23 by madorna-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static char	*search_command(char *path, char *command);
static char	*search_path(char *path, char *command);

/*
** - Después del tokenizado, una vez identificado cuál es el builtin
** hago la llamada de ejecución del comando
** - Los pasos son:
**		- Compruebo si es uno de mis builtin, si es así, lo ejecuto (TO-DO)
**		- Si no es uno de mis builtin, usaré execve para que funcione. Compruebo
**		si lo que me pasan es ya una ruta con /, y ejecuto
**		- Si no es uno de mis builtin, usaré execve para que funcione. Si solo
**		me pasan el builtin busco en PATH si alguna de las rutas concatenada con
**		el builtin es válida y si lo es ejecuto la orden, si no devuelvo error
*/

void
	exec_command(t_minishell *mini, char *command, char **argv, char **env)
{
	char	*new_command;
	char	*path;

	(void)argv;
	(void)env;
	if (is_builtin(command))
		builtin(argv, mini);
	else
	{
		if (is_path(command))
			my_execve(command, argv, env);
		else
		{
			path = get_value(mini->env_list, "PATH");
			new_command = search_path(path, command);
			if (new_command == NULL)
			{
				printf("\nminishell: %s: command not found\n", command);
				return ;
			}
			mini->errno = my_execve(new_command, argv, env);
			free(new_command);
		}
	}
}

static inline void
	path_check(int fd, char *aux2)
{
	if (fd >= 0)
		close(fd);
	else
	{
		free(aux2);
		aux2 = NULL;
	}
}

/*
** Si no es uno de mis builtin, y no me han pasado una ruta, compruebo si puedo
** acceder al builtin desde alguna de las rutas que hay en mi PATH
*/

static char
	*search_path(char *path, char *command)
{
	char	*my_path;
	char	*after;
	char	*aux;
	char	*aux2;
	int		fd;

	aux2 = NULL;
	my_path = ft_strdup(path);
	after = ft_strchr(my_path, ':');
	while (after)
	{
		*after = '\0';
		aux = ft_strjoin(my_path, "/");
		aux2 = ft_strjoin(aux, command);
		free(aux);
		fd = open(aux2, O_RDONLY);
		if (fd >= 0)
			break ;
		ft_memmove(my_path, after + 1, ft_strlen(after + 1));
		after = ft_strchr(my_path, ':');
	}
	free(my_path);
	path_check(fd, aux2);
	return (aux2);
}

int
	my_execve(char *command, char **argv, char **env)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		ft_putstr_fd("\n", 1);
		execve(command, argv, env);
	}
	else if (pid > 0)
		pid = wait(&status);
	else
		ft_putstr_fd("", 1);
	status = WEXITSTATUS(status);
	return (status);
}

/*int my_execve(char *command, char **argv, char **env)
{
	fork()
	- Crea otro proceso idéntico al que tengo, con otro pid (un clon)
	RETURN
	- Dicha función va a regresar un valor tanto al proceso original (padre)
	como al nuevo proceso (hijo)
	- Al proceso padre le va a regresar el pid de su hijo
	- Al proceso hijo le va a regresar 0.
	
	- Lo que hago es un if para decirle lo que tiene que hacer:
		- Si estoy en el hijo llamo a execve
}*/