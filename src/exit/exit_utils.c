/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 10:51:37 by rcompain          #+#    #+#             */
/*   Updated: 2026/02/04 18:31:47 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/mini_shell.h"

void	print_error(char *name, char *arg, char c, char *msg)
{
	write(2, "minishell: ", 11);
	if (name)
	{
		write(2, name, ft_strlen(name));
		write(2, ": ", 2);
	}
	if (arg)
	{
		write(2, arg, ft_strlen(arg));
		write(2, ": ", 2);
	}
	if (c)
	{
		write(2, &c, 1);
		write(2, ": ", 2);
	}
	if (msg)
	{
		write(2, msg, ft_strlen(msg));
		write(2, "\n", 1);
	}
	else
		perror(NULL);
}

void	call_to_exit(t_data *shell, int status, char *msg)
{
	if (msg)
		write(2, msg, ft_strlen(msg));
	shell->exit = true;
	shell->exit_status = status;
}

void	check_exit_flag(t_data *shell)
{
	if (g_exit_flag != 1)
		return ;
	shell->exit = true;
	shell->exit_status = SIGTERM_EXIT;
}
