/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 14:09:48 by rcompain          #+#    #+#             */
/*   Updated: 2026/01/26 11:27:45 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/mini_shell.h"

static void	exec_echo(t_echo *echo, char **args)
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
	if (echo->n == false)
		ft_printf("\n");
}

static void	add_echo_options(t_echo *echo, char *arg)
{
	int	i;

	i = 0;
	while (arg[++i])
	{
		if (arg[i] == 'n')
			echo->n = true;
		if (arg[i] == 'e')
			echo->e = true;
		if (arg[i] == 'E')
			echo->e_capital = true;
	}
}

void	echo_cmd(char **args)
{
	t_echo	echo;
	int		i;

	ft_memset(&echo, 0, sizeof(t_echo));
	i = 0;
	while (args[i])
	{
		if (check_is_options(args[i], "enE") == true)
			add_echo_options(&echo, args[i]);
		else
		{
			exec_echo(&echo, &args[i]);
			break ;
		}
		i++;
	}
}
