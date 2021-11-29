/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madorna- <madorna-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 06:36:55 by madorna-          #+#    #+#             */
/*   Updated: 2021/11/29 08:32:29 by madorna-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void
	skip_lst_spaces(t_list **lst)
{
	while ((*lst) && ((t_chars*)(*lst)->content)->c == ' ')
		*lst = (*lst)->next;
}


// FIXME: taking bad names
char
	*manage_dollar(t_list **lst)
{
	char	*env_var;
	int		i;

	env_var = calloc(1024, sizeof(char));
	i = 0;
	while ((*lst) && ((((t_chars*)(*lst)->content)->flag & DOLLAR)
		== DOLLAR) == 1)
	{
		env_var[i++] = ((t_chars*)(*lst)->next->content)->c;
		*lst = (*lst)->next;
	}
	return (env_var);
}

void
	print2(void *content)
{
	printf("%s\n", (char*)content);
}

void
	iter_l_argv(void *lst)
{
	printf("Command:\n");
	ft_lstiter(((t_cmd*)lst)->l_argv, print2);
	printf("End of Command\n");
}

// FIXME: Revisar creación de comandos
void
	make_command(t_mini *mini)
{
	t_list	*lst;
	t_cmd	*cmd;
	int		i;

	lst = mini->chars;
	cmd = calloc(1, sizeof(t_cmd));
	mini->buffer = calloc(1024, sizeof(char));
	i = 0;
	while (lst)
	{
		if (((t_chars*)lst->content)->c == ' ' && (((((t_chars*)(lst)->content)->flag & QUOTE)
				== QUOTE) != 1) && (((((t_chars*)(lst)->content)->flag
				& DQUOTE) == DQUOTE) != 1))
		{
			skip_lst_spaces(&lst);
			if (!cmd->l_argv)
				cmd->l_argv = ft_lstnew(mini->buffer);
			else
				ft_lstadd_back(&cmd->l_argv, ft_lstnew(mini->buffer));
			mini->buffer = calloc(1024, sizeof(char));
			i = 0;
		}
		if (((((t_chars*)(lst)->content)->flag & DOLLAR) == DOLLAR) == 1)
			printf("ENV [%s]\n", getenv(manage_dollar(&lst)));
		if (((t_chars*)lst->content)->c == '|')
		{
			ft_lstadd_back(&cmd->l_argv, ft_lstnew(mini->buffer));
			ft_lstadd_back(&mini->cmds, ft_lstnew(cmd));
			cmd = calloc(1, sizeof(t_cmd));
			mini->buffer = calloc(1024, sizeof(char));
			i = 0;
		}
		mini->buffer[i++] = ((t_chars*)lst->content)->c;
		lst = lst->next;
	}
	ft_lstadd_back(&mini->cmds, ft_lstnew(cmd));
	ft_lstiter(mini->cmds, iter_l_argv);
	mini->cmds = NULL;
	// ft_lstadd_back(&cmd->l_argv, ft_lstnew(str));
	printf("\n");
}
