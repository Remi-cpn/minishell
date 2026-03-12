/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_arg.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tseche <tseche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 10:30:34 by rcompain          #+#    #+#             */
/*   Updated: 2026/03/12 11:12:36 by tseche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/mini_shell.h"

static void	update_flag(int *flag, char c)
{
	if (!*flag && (c == '"' || c == '\''))
		*flag += (2 * (c == '"')) + (c == '\'');
	else if ((*flag == 2 && c == '"') || (*flag == 1 && c == '\''))
		*flag = 0;
}

static int	add_to_key(char **key, char *arg, int flag)
{
	int	start;
	int	i;
	int	j;

	i = 0;
	j = 0;
	start = 0;
	while (arg && arg[i])
	{
		update_flag(&flag, arg[i]);
		if (arg[i] == '*' && !flag)
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
	int	flag;

	i = 0;
	count = 0;
	flag = 0;
	while (s && s[i])
	{
		update_flag(&flag, s[i]);
		if (s[i] == '*' && !flag)
			count++;
		i++;
	}
	return (count);
}

int	find_arg_wc(char **args, char ***key)
{
	int		i;
	int		c_stars;
	int		flag;

	i = 0;
	while (args[i])
	{
		c_stars = count_stars(args[i]);
		if (c_stars > 0)
		{
			*key = ft_calloc(c_stars + 2, sizeof(char *));
			if (!*key)
				return (FAILURE);
			flag = add_to_key(*key, args[i], 0);
			if (flag != SUCCES)
				break ;
			dequote_range(*key, 0, c_stars + 1);
			return (i);
		}
		i++;
	}
	free_array(*key);
	return (FAILURE);
}
