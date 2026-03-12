/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tseche <tseche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 09:27:24 by rcompain          #+#    #+#             */
/*   Updated: 2026/03/12 14:00:06 by tseche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/mini_shell.h"
#include <limits.h>

static void	select_error(t_data *shell, bool b, int status, bool print_ok)
{
	shell->exit = b;
	if (status == EXIT_NOT_NUMERIC && print_ok == true)
		print_error("exit", NULL, 0, "numeric argument required");
	else if (status == EXIT_TO_MANY_ARGS && print_ok == true)
		print_error("exit", NULL, 0, "too many arguments");
	shell->error_status = status;
}

static void	check_num(t_exit *exit, char *arg)
{
	int	i;

	i = 0;
	if (arg[0] == '-' || arg[0] == '+')
		i++;
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
		{
			exit->not_num = true;
			return ;
		}
		i++;
	}
	if (arg && arg[0] == 0)
		exit->not_num = true;
}

void	exit_cmd(t_data *shell, char **args)
{
	t_exit	exit;
	long	num;

	ft_memset(&exit, 0, sizeof(t_exit));
	if (shell->is_child == false)
		write(2, "exit\n", 5);
	if (!args[1])
		call_to_exit(shell, shell->error_status, NULL);
	if (!args[1])
		return ;
	if (args[2])
		exit.many_args = true;
	check_num(&exit, args[1]);
	if (exit.not_num == true)
		select_error(shell, true, EXIT_NOT_NUMERIC, true);
	else if (exit.many_args == true && exit.not_num == false)
		select_error(shell, false, EXIT_TO_MANY_ARGS, true);
	else
	{
		num = ft_atol(args[1]);
		if (num > INT_MAX || num < INT_MIN)
			select_error(shell, true, EXIT_NOT_NUMERIC, true);
		else
			select_error(shell, true, num, false);
	}
}
