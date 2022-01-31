/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madorna- <madorna-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 13:01:11 by madorna-          #+#    #+#             */
/*   Updated: 2022/01/31 02:17:40 by madorna-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

inline static void
	free_cd(char *p, char *dir)
{
	if (p)
		free(p);
	if (dir)
		free(dir);
}

inline static int
	cd_check(char **argv, char *p, char *dir)
{
	if (chdir(argv[1]) <= -1)
	{
		printf("\n%s: cd: ", SHELL_NAME);
		ft_putstr_fd(argv[1], 1);
		if (open(argv[1], O_RDONLY) > 0)
		{
			ft_putstr_fd(": Not a directory\n", 1);
			free_cd(p, dir);
			return (1);
		}
		ft_putstr_fd(": No such file or directory\n", 1);
		free_cd(p, dir);
		return (1);
	}
	return (0);
}

/*
** builtin: cd -> cd usa getcwd, no PWD! -> chdir!
** 1.	Ver si directorio existe
** 2.	Si no existe -> bash: cd: df: No such file or directory
**		Si existe -> $OLDPWD = $PWD; entrar en carpeta; $PWD = dir
** Si no hay opciones -> cd $HOME
** cd solamente usa el primer argumento, el resto los ignora. (En Darwin)
** Si hay argumento pero está vacío ("", ''), cd no hace nada.
** Keep in mind that cd just has to work only with relative or absolute paths !
*/

int
	ft_cd(int argc, char **argv, t_list *env)
{
	char		*p;
	char		*dir;

	p = NULL;
	dir = NULL;
	(void)argc;
	if (!argv[1])
		argv[1] = getenv("HOME");
	if (!ft_strncmp(argv[1], "\"\"", ft_strlen(argv[1])) || !ft_strncmp(argv[1], "\'\'", ft_strlen(argv[1])))
	{
		write(1, "\n", 1);
		return (0);
	}
	p = ft_strdup(argv[1]);
	while ((ft_strlen(p) - 1) != 0 && p[ft_strlen(p) - 1] == '/')
		p[ft_strlen(p) - 1] = '\0';
	if (cd_check(argv, p, dir))
		return (1);
	write(1, "\n", 1);
	dir = getcwd(dir, 0);
	// set_value(env, "OLDPWD", dir, (char *)__FUNCTION__);
	// set_value(env, "PWD", argv[1], (char *)__FUNCTION__);
	free_cd(p, dir);
	return (0);
}
