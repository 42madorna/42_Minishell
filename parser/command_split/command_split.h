/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_split.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaliste <agaliste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 17:07:58 by agaliste          #+#    #+#             */
/*   Updated: 2022/02/27 17:18:05 by agaliste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_SPLIT_H
# define COMMAND_SPLIT_H

struct	s_mini;
struct	s_list;

void	manage_pipe(struct s_mini *mini, struct s_list **chars);
int		manage_in(struct s_mini *mini, struct s_list **chars);
int		manage_out(struct s_mini *mini, struct s_list **chars);
char	*seek_name(struct s_mini *mini, struct s_list **chars, int flag);
void	skip_lst_spaces(struct s_list **lst);
int		ft_is_valid_char(char c);

#endif