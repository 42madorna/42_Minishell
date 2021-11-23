/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dellast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaliste <agaliste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 10:35:23 by agaliste          #+#    #+#             */
/*   Updated: 2021/09/21 15:30:57 by agaliste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel_last(t_list *lst)
{
	t_list	*temp;
	int		n;
	int		i;

	n = ft_lstsize(lst);
	temp = lst;
	i = 1;
	while (++i < n)
		temp = temp->next;
	free(temp->next);
	temp->next = NULL;
}
