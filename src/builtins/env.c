/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 14:54:11 by rcompain          #+#    #+#             */
/*   Updated: 2026/02/03 11:27:50 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/mini_shell.h"

void	env_cmd(t_data *shell, char **args)
{
	int		i;

	i = 0;
	if (args && args[0] && args[1])
	{
		shell->exit_status = ERR_CMD_NOT_FOUND;
		print_error("env", NULL, 0, "too many arguments");
		return ;
	}
	while (shell->env[i])
	{
		ft_printf("%s\n", shell->env[i]);
		i++;
	}
	shell->exit_status = 0;
}
