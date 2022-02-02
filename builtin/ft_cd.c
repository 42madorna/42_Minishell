/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madorna- <madorna-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 13:01:11 by madorna-          #+#    #+#             */
/*   Updated: 2022/02/03 00:37:57 by madorna-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

inline static void
	free_cd(char *dir)
{
	if (dir)
		free(dir);
}

inline static int
	cd_check(char **argv, char *dir)
{
	if (chdir(argv[1]) <= -1)
	{
		printf("%s: cd: %s: ", SHELL_NAME, argv[1]);
		if (open(argv[1], O_RDONLY) > 0)
		{
			printf("Not a directory\n");
			free_cd(dir);
			return (0);
		}
		printf("No such file or directory\n");
		free_cd(dir);
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

/*
** FIXME: [MINS-84] cd builtin when env is unset
*/
int
	ft_cd(int argc, char **argv, t_list *l_env)
{
	char		*dir;

	dir = NULL;
	(void)argc;
	if (!argv[1])
	{
		argv[1] = ft_env_value(l_env, "HOME");
		if (!argv[1])
		{
			printf("%s: cd: HOME not set\n", SHELL_NAME);
			return (0);
		}
	}
	if (!ft_strncmp(argv[1], "\"\"", ft_strlen(argv[1]))
		|| !ft_strncmp(argv[1], "\'\'", ft_strlen(argv[1])))
		return (0);
	if (cd_check(argv, dir))
		return (1);
	dir = getcwd(dir, 0);
	ft_env_set_value(l_env, "OLDPWD", ft_env_value(l_env, "PWD"));
	ft_env_set_value(l_env, "PWD", dir);
	free_cd(dir);
	return (0);
}
