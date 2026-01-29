/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 14:09:48 by rcompain          #+#    #+#             */
/*   Updated: 2026/01/29 11:13:50 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/mini_shell.h"

static void	exec_echo(bool n, char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		ft_printf("%s", args[i]);
		if (args[i + 1])
			ft_printf(" ");
		i++;
	}
	if (n == false)
		ft_printf("\n");
}

/**
 * This function checks if the char *arg is composed only of options.
 */
static bool	check_is_options(char *arg, char *key)
{
	int	i;
	int	j;
	int	flag;

	i = 0;
	if (arg[0] != '-')
		return (false);
	if (!arg[1])
		return (false);
	while (arg[++i])
	{
		j = 0;
		flag = 0;
		while (key[j] && flag == 0)
		{
			if (arg[i] == key[j])
				flag = 1;
			j++;
		}
		if (flag == 0)
			return (false);
	}
	return (true);
}

void	echo_cmd(char **args)
{
	int		i;
	bool	n;

	if (!args || !args[0])
	{
		ft_printf("\n");
		return ;
	}
	n = false;
	i = 0;
	while (args[i])
	{
		if (check_is_options(args[i], "n") == true)
			n = true;
		else
		{
			exec_echo(n, &args[i]);
			break ;
		}
		i++;
	}
}
