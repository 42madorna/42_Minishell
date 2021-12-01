/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madorna- <madorna-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 06:36:55 by madorna-          #+#    #+#             */
/*   Updated: 2021/12/01 04:20:41 by madorna-         ###   ########.fr       */
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
	*manage_dollar(t_mini *mini, t_list **lst, int *pos)
{
	char	*env_var;
	char	*env_cont;
	int		i;

	i = 0;
	env_var = calloc(1024, sizeof(char));
	// printf("$");
	while ((*lst) && ((((t_chars*)(*lst)->content)->flag & DOLLAR)
		== DOLLAR) == 1 && ((t_chars*)(*lst)->content)->c)
	{
		env_var[i++] = ((t_chars*)(*lst)->content)->c;
		// printf("%c", ((t_chars*)(*lst)->content)->c);
		*lst = (*lst)->next;
	}
	// printf("\n");
	env_cont = getenv(env_var);
	while (env_cont && *env_cont)
		mini->buffer[(*pos)++] = *env_cont++;
	(*pos)++;
	return (env_var);
}

int
	manage_append(t_mini *mini, t_list **lst, int *pos)
{
	char	*file;
	int		fd;
	int		i;

	i = 0;
	file = calloc(1024, sizeof(char));
	// printf("$");
	while ((*lst) && ((((t_chars*)(*lst)->content)->flag & APPEND)
		== APPEND) == 1 && ((t_chars*)(*lst)->content)->c)
	{
		file[i++] = ((t_chars*)(*lst)->content)->c;
		// printf("%c", ((t_chars*)(*lst)->content)->c);
		*lst = (*lst)->next;
	}
	// printf("\n");
	fd = open(file, O_APPEND | O_CREAT | O_RDONLY | O_WRONLY);
	// (*pos)++;
	return (fd);
}

int
	manage_in(t_mini *mini, t_list **lst, int *pos)
{
	char	*file;
	int		fd;
	int		i;

	i = 0;
	file = calloc(1024, sizeof(char));
	// printf("$");
	while ((*lst) && ((((t_chars*)(*lst)->content)->flag & IN)
		== IN) == 1 && ((t_chars*)(*lst)->content)->c)
	{
		file[i++] = ((t_chars*)(*lst)->content)->c;
		// printf("%c", ((t_chars*)(*lst)->content)->c);
		*lst = (*lst)->next;
	}
	// printf("\n");
	fd = open(file, O_RDONLY);
	// (*pos)++;
	return (fd);
}

int
	manage_out(t_mini *mini, t_list **lst, int *pos)
{
	char	*file;
	int		fd;
	int		i;

	i = 0;
	file = calloc(1024, sizeof(char));
	// printf("$");
	while ((*lst) && ((((t_chars*)(*lst)->content)->flag & OUT)
		== OUT) == 1 && ((t_chars*)(*lst)->content)->c)
	{
		file[i++] = ((t_chars*)(*lst)->content)->c;
		printf("%c", ((t_chars*)(*lst)->content)->c);
		*lst = (*lst)->next;
	}
	// printf("\n");
	fd = open(file, O_WRONLY | O_CREAT);
	// (*pos)++;
	return (fd);
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
/*
** At this moment, ARGV is constructed ok but
** 	FIXME: Spaces after PIPE
** 	TODO: APPEND, DELIMITTER, IN, OUT
*/
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
		if (((t_chars*)lst->content)->c == ' ' &&
			(((((t_chars*)(lst)->content)->flag & QUOTE) == QUOTE) != 1)
			&& (((((t_chars*)(lst)->content)->flag & DQUOTE) == DQUOTE) != 1))
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
			manage_dollar(mini, &lst, &i);
		if (((t_chars*)lst->content)->c == '|')
		{
			if (!cmd->l_argv)
			{
				printf("Unexpected `|'\n");
				return ;
			}
			lst = lst->next;
			ft_lstadd_back(&cmd->l_argv, ft_lstnew(mini->buffer));
			ft_lstadd_back(&mini->cmds, ft_lstnew(cmd));
			cmd = calloc(1, sizeof(t_cmd));
			mini->buffer = calloc(1024, sizeof(char));
			i = 0;
		}
		if (((((t_chars*)(lst)->content)->flag & APPEND) == APPEND) == 1)
			cmd->outfile = manage_append(mini, &lst, &i);
		if (((((t_chars*)(lst)->content)->flag & IN) == IN) == 1)
			cmd->infile = manage_in(mini, &lst, &i);
		if (((((t_chars*)(lst)->content)->flag & DELIMITER) == DELIMITER) == 1)
			printf ("TODO: Manage delimitter [MINS-57]!\n");
		if (((t_chars*)(lst)->content)->flag == OUT)
			cmd->outfile = manage_out(mini, &lst, &i);
		mini->buffer[i++] = ((t_chars*)lst->content)->c;
		if (((t_chars*)lst->content)->c == ' ' && (((((t_chars*)(lst)->content)->flag & QUOTE)
				== QUOTE) != 1) && (((((t_chars*)(lst)->content)->flag
				& DQUOTE) == DQUOTE) != 1))
			continue ;
		lst = lst->next;
	}
	ft_lstadd_back(&cmd->l_argv, ft_lstnew(mini->buffer));
	ft_lstadd_back(&mini->cmds, ft_lstnew(cmd));
	// ft_lstiter(mini->cmds, iter_l_argv);
	// ft_lstadd_back(&cmd->l_argv, ft_lstnew(str));
	// printf("\n");
}
