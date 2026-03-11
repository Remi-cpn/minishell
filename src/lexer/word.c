/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: von <von@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 16:55:23 by tseche            #+#    #+#             */
/*   Updated: 2026/03/11 23:08:40 by von              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ast.h"
#include "../../libft/libft.h"
#include <errno.h>

size_t	len_quoted(char *src, char q)
{
	char	*s;

	s = src;
	while (*src && *src != q)
		src++;
	if (*src == q)
		return (src - s + 1);
	return (-1);
}

int	is_start_word(char c)
{
	return ((!ft_isoneof(c, "&|()<>")));
}

int	digits(char *src)
{
	int	i;

	i = 0;
	while (src[i] && ft_isdigit(src[i]))
		i++;
	return (i);
}

int	len_word(char *src)
{
	int	i;
	int	len_quote;

	i = 0;
	if (ft_isdigit(src[i]))
		return (digits(src));
	while (src[i])
	{
		if ((src[i] == '\"' || src[i] == '\''))
		{
			i++;
			len_quote = len_quoted(&src[i], src[i - 1]);
			if (len_quote == -1)
				report_parsing_error(src[i], NULL);
			if (len_quote == -1)
				return (-1);
			i += len_quote;
		}
		else if (!ft_iswhitespace(src[i]) && !ft_isoneof(src[i], "&|<>()"))
			i++;
		else
			break ;
	}
	return (i);
}
