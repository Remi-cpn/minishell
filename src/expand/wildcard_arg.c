/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_arg.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 10:30:34 by rcompain          #+#    #+#             */
/*   Updated: 2026/03/05 13:27:22 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/mini_shell.h"

/*
static char	*ft_strndup(char *s, int start, int n, int free_s)
{
	char	*dup;
	char	*string;

	if (start < n)
	{
		string = s + start;
		dup = (char *)malloc(sizeof(char) * (n - start + 1));
		if (dup)
			dup = ft_memcpy(dup, string, n - start);
	}
	else
	{
		dup = malloc(sizeof(char));
		if (dup)
			dup[0] = '\0';
	}
	if (free_s == 1)
		ft_freenull((void *)s);
	return (dup);
}
*/

static void	add_to_key(char **key, char *arg)
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
				return ;
			j++;
			start = i + 1;
		}
		i++;
	}
	key[j] = ft_strndup(arg, start, i);
	if (!key[j])
		return ;
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

	i = 0;
	while (args[i])
	{
		tmp = ft_strchr(args[i], '*');
		if (tmp)
		{
			c_stars = count_stars(args[i]);
			*key = ft_calloc(c_stars + 2, sizeof(char *));
			if (!*key)
				return (-1);
			add_to_key(*key, args[i]);
			return (i);
		}
		i++;
	}
	return (-1);
}
