/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 09:27:24 by rcompain          #+#    #+#             */
/*   Updated: 2026/01/26 17:11:19 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/mini_shell.h"

static void	select_error(t_data *shell, bool b, int status)
{
	shell->exit = b;
	if (status == EXIT_NOT_NUMERIC)
		write(2, "exit: numeric argument required\n", 32);
	else if (status == EXIT_TO_MANY_ARGS)
		write(2, "exit: too many arguments\n", 25);
	shell->exit_status = status;
}

static void	check_num(t_exit *exit, char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
		{
			exit->not_num = true;
			return ;
		}
		i++;
	}
}

void	exit_cmd(t_data *shell, char **args)
{
	t_exit	exit;

	ft_memset(&exit, 0, sizeof(t_exit));
	write(2, "error\n", 6);
	if (!args[0])
	{
		shell->exit = true;
		return ;
	}
	if (args[1])
		exit.many_args = true;
	check_num(&exit, args[0]);
	if (exit.not_num == true)
		select_error(shell, true, EXIT_NOT_NUMERIC);
	else if (exit.many_args == true && exit.not_num == false)
		select_error(shell, false, EXIT_TO_MANY_ARGS);
	else
		select_error(shell, true, ft_atol(args[0]) % 256);
}
