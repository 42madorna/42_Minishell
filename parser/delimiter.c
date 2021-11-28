/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delimiter.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madorna- <madorna-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 23:25:46 by madorna-          #+#    #+#             */
/*   Updated: 2021/11/28 05:52:22 by madorna-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** If no word is after DELIMITER (<<), error.
** Add words to (t_list*)mini->delimiters and not to buffer!
*/
int
	parse_delimiter(t_mini *mini)
{
	mini->flag += DELIMITER;
	printf("Called Delimiter function\n");
	return (0);
}
