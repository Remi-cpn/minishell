/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 13:38:56 by rcompain          #+#    #+#             */
/*   Updated: 2026/02/03 11:28:32 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/mini_shell.h"

void	pwd_cmd(t_data *shell, char **args)
{
	int		i;

	shell->error_status = SUCCES;
	if (args && args[0] && args[1])
	{
		shell->error_status = ERR_CMD_NOT_FOUND;
		print_error("pwd", NULL, 0, "too many arguments");
		return ;
	}
	i = 0;
	while (shell->env[i])
	{
		if (ft_strncmp(shell->env[i], "PWD=", 4) == 0)
		{
			ft_printf("%s\n", shell->env[i] + 4);
			shell->error_status = SUCCES;
			return ;
		}
		i++;
	}
	shell->error_status = ERROR;
	print_error("pwd", NULL, 0, "error retrieving current directory");
}
