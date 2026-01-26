/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 09:27:24 by rcompain          #+#    #+#             */
/*   Updated: 2026/01/26 12:26:34 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/mini_shell.h"

void	exit_cmd(t_data *shell, char **args)
{
	int	i;

	ft_printf("exit\n");
	if (!args[0])
	{
		shell->exit = true;
		return ;
	}
	i = -1;
	while (args[0][++i] && shell->exit == false)
	{
		if (!ft_isdigit(args[0][i]))
		{
			write(2, "exit: numeric argument required", 31);
			shell->exit_status = EXIT_NOT_NUMERIC;
			shell->exit = true;
		}
	}
	if (args[1])
	{
		shell->exit = false;
		if (shell->exit != EXIT_NOT_NUMERIC)
		{
			write(2, "exit: too many arguments", 24);
			shell->exit_status = EXIT_TO_MANY_ARGS;
			shell->exit = true;
		}
	}
	if (shell->exit_status != EXIT_TO_MANY_ARGS && shell->exit != EXIT_NOT_NUMERIC)
		call_to_exit(&shell, ft_atol(args[0]) % 256);
}
