/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madorna- <madorna-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 00:49:50 by madorna-          #+#    #+#             */
/*   Updated: 2021/11/23 01:25:04 by madorna-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int
	main(int argc, char **argv, char **env)
{
	t_mini mini;
	char cosa;

	ft_bzero(&mini, sizeof(t_mini));
	mini.argc = argc;
	mini.argv = argv;
	mini.env = env;
	printf("%d\n", mini.argc);
	while (1)
	{
		printf("minishell$ ");
		scanf("%s", &cosa);
	}
}
