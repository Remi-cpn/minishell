/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: von <von@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 10:14:36 by tseche            #+#    #+#             */
/*   Updated: 2026/03/05 20:34:26 by von              ###   ########.fr       */
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
	int	addquote;
	int	squote;
	int	dquote;

	flag = 0;
	len = 0;
	while (*str)
	{
		squote = (*str == '\'');
		dquote = (*str == '"');
		addquote = (2 * dquote) + squote;
		if (!flag && (squote || dquote))
			flag += addquote;
		else if (!ft_isoneof(*str, IFS) || (flag && ft_isoneof(*str, IFS)))
			len++;
		else
			break ;
		if ((flag == 2 && dquote) || (flag == 1 && squote))
			flag -= addquote;
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
		if (!flag && !ft_isoneof(*string, IFS) && count++)
			flag++;
		else if (ft_isoneof(*string, IFS) && !flag)
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
		res[j] = ft_strndup(str, 0, len);
		if (!res[j])
			free_array(res);
		if (!res[j++])
			return (NULL);
		str += len;
	}
	return (res);	
}
