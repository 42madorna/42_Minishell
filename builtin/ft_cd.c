/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madorna- <madorna-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 13:01:11 by madorna-          #+#    #+#             */
/*   Updated: 2022/03/08 16:42:49 by madorna-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

inline static int
	free_cd(char *dir, char *arg, char *pwd, int ret)
{
	if (dir)
		free(dir);
	if (arg)
		free(arg);
	if (pwd)
		free(pwd);
	return (ret);
}

inline static int
	cd_check(char **argv)
{
	if (chdir(argv[1]) <= -1)
	{
		ft_putstr_fd(SHELL_NAME ": cd: ", 2);
		printcustom(argv[1], ": ", 2);
		if (open(argv[1], O_RDONLY) > 0)
		{
			ft_putstr_fd("Not a directory\n", 2);
			return (1);
		}
		ft_putstr_fd("No such file or directory\n", 2);
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
	ft_cd(int argc, char **argv, t_list *l_env)
{
	char	*dir;
	char	*pwd;

	dir = NULL;
	(void)argc;
	if (!argv[1])
	{
		argv[1] = ft_env_value(l_env, "HOME");
		if (!argv[1])
		{
			ft_putstr_fd(SHELL_NAME ": cd: HOME not set\n", 2);
			return (1);
		}
	}
	if (!ft_strncmp(argv[1], "\"\"", ft_strlen(argv[1]))
		|| !ft_strncmp(argv[1], "\'\'", ft_strlen(argv[1])))
		return (free_cd(dir, argv[1], NULL, 0));
	if (cd_check(argv))
		return (free_cd(dir, NULL, NULL, 1));
	dir = getcwd(dir, 0);
	pwd = ft_env_value(l_env, "PWD");
	ft_env_set_value(l_env, "OLDPWD", pwd);
	ft_env_set_value(l_env, "PWD", dir);
	free_cd(dir, NULL, pwd, 0);
	return (0);
}
