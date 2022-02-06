/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madorna- <madorna-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 01:01:48 by madorna-          #+#    #+#             */
/*   Updated: 2022/02/06 05:19:33 by madorna-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


/*
** TODO: [MINS-85] Convert t_env to char **env
*/
void
	ft_list_to_env(t_mini *mini)
{
	t_list	*l_env;
	t_env	*env_node;
	int		n_env;
	int		i;

	l_env = mini->l_env;
	n_env = ft_lstsize(l_env);
	mini->env_cmd = calloc(n_env + 1, sizeof(char*));
	i = 0;
	while (l_env)
	{
		env_node = l_env->content;
		mini->env_cmd[i] = ft_strjoin_env(env_node->key, env_node->value);
		if (mini->env_cmd[i])
			++i;
		l_env = l_env->next;
	}
}

void
	make_env(t_mini *mini)
{
	t_list	*cmds;

	cmds = mini->cmds;
	ft_list_to_env(mini);
	while (cmds)
	{
		((t_cmd *)(cmds->content))->env = mini->env_cmd;
		cmds = cmds->next;
	}
}
