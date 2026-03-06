/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 10:14:36 by tseche            #+#    #+#             */
/*   Updated: 2026/03/06 15:00:40 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/mini_shell.h"

int	skip_pattern(char *str, char *p)
{
	char	*src;

	src = str;
	while (*str && ft_isoneof(*str, p) && str++)
		;
	return (str - src);
}

int	lenword(char *str)
{
	int	flag;
	int	len;
	int	squote;
	int	dquote;

	flag = 0;
	len = 0;
	while (*str)
	{
		squote = (*str == '\'');
		dquote = (*str == '"');
		len++;
		if ((flag == 2 && dquote) || (flag == 1 && squote))
			flag -= (2 * dquote) + squote;
		else if (!flag && (squote || dquote))
			flag += (2 * dquote) + squote;
		else if (ft_isoneof(*str, IFS) && !flag)
		{
			len--;
			break ;
		}
		str++;
	}
	return (len);
}

int	countwsep(char *string)
{
	int	count;
	int	flag;

	flag = 1;
	count = 0;
	while (*string)
	{
		if (flag && !ft_isoneof(*string, IFS))
		{
			count++;
			flag = 0;
		}
		else if (!flag && ft_isoneof(*string, IFS))
			flag = 1;
		string++;
	}
	return (count);
}


char	**split_expand(char *str)
{
	char	**res;
	int		j;
	int		len;
	int		nbsep;

	nbsep = countwsep(str);
	res = ft_calloc(sizeof(char *), (nbsep + 1));
	if (!res)
		return (NULL);
	j = 0;
	len = 0;
	while (*str)
	{
		str += skip_pattern(str, IFS);
		len = lenword(str);
		if (len == 0)
			continue ;
		res[j] = ft_strndup(str, 0, len - 1);
		if (!res[j])
			free_array(res);
		if (!res[j++])
			return (NULL);
		str += len;
	}
	return (res);
}
