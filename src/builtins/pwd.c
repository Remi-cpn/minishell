/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 13:38:56 by rcompain          #+#    #+#             */
/*   Updated: 2026/01/29 15:38:06 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/mini_shell.h"

void	pwd_cmd(t_data *shell, char **args)
{
	int		i;

	if (args || args[0])
	{
		shell->exit_status = ERR_CMD_NOT_FOUND;
		write(2, "pwd: too many arguments\n", 24);
		return ;
	}
	i = 0;
	while (shell->env[i])
	{
		if (ft_strncmp(shell->env[i], "PWD=", 4) == 0)
		{
			ft_printf("%s\n", shell->env[i] + 4);
			shell->exit_status = SUCCES;
			return ;
		}
		i++;
	}
	shell->exit_status = ERR_PWD;
	write(2, "pwd: error retrieving current directory\n", 40);
}
