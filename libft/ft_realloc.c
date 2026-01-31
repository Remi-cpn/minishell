/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tseche <tseche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 15:55:19 by tseche            #+#    #+#             */
/*   Updated: 2026/01/31 16:19:23 by tseche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc.h>
#include "./libft.h"

void	*ft_realloc(void *p, size_t n)
{
	void	*ptr;

	if (n == 0 && p != NULL)
	{
		free(p);
		return (NULL);
	}
	else if (!p)
	{
		p = malloc(n);
		if (!p)
			return (NULL);
		return (p);
	}
	ptr = malloc(n);
	if (!ptr)
		return (NULL);
	if (p)
		ft_memcpy(ptr, p, n - 1);
	((unsigned char *)ptr)[n - 1] = 0;
	free(p);
	return (ptr);
}
