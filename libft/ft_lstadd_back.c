/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 08:34:39 by rcompain          #+#    #+#             */
/*   Updated: 2025/10/22 11:36:50 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*lst_tmp;

	lst_tmp = *lst;
	if (!lst || !new)
		return ;
	if (!*lst)
		*lst = new;
	else
	{
		lst_tmp = ft_lstlast(*lst);
		lst_tmp->next = new;
	}
}
