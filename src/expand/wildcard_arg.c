/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_arg.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 10:30:34 by rcompain          #+#    #+#             */
/*   Updated: 2026/03/05 16:53:59 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/mini_shell.h"

static int	add_to_key(char **key, char *arg)
{
	int	start;
	int	i;
	int	j;

	i = 0;
	j = 0;
	start = 0;
	while (arg && arg[i])
	{
		if (arg[i] == '*')
		{
			key[j] = ft_strndup(arg, start, i - 1);
			if (!key[j])
				return (ERROR);
			j++;
			start = i + 1;
		}
		i++;
	}
	key[j] = ft_strndup(arg, start, i);
	if (!key[j])
		return (ERROR);
	return (SUCCES);
}

static int	count_stars(char *s)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s && s[i])
	{
		if (s[i] == '*')
			count++;
		i++;
	}
	return (count);
}

int	find_arg_wc(char **args, char ***key)
{
	int		i;
	int		c_stars;
	char	*tmp;
	int		flag;

	i = 0;
	while (args[i])
	{
		tmp = ft_strchr(args[i], '*');
		if (tmp)
		{
			c_stars = count_stars(args[i]);
			*key = ft_calloc(c_stars + 2, sizeof(char *));
			if (!*key)
				return (FAILURE);
			flag = add_to_key(*key, args[i]);
			if (flag != SUCCES)
				break ;
			return (i);
		}
		i++;
	}
	free_array(*key);
	return (FAILURE);
}
