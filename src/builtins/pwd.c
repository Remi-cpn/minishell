/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 13:38:56 by rcompain          #+#    #+#             */
/*   Updated: 2026/03/12 00:40:48 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/mini_shell.h"

void	pwd_cmd(t_data *shell, char **args)
{
	char	*cwd;

	shell->error_status = SUCCES;
	if (args && args[0] && args[1])
	{
		shell->error_status = ERR_CMD_NOT_FOUND;
		print_error("pwd", NULL, 0, "too many arguments");
		return ;
	}
	cwd = get_env(shell, "PWD=");
	if (cwd)
	{
		ft_printf("%s\n", cwd);
		return ;
	}
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		shell->error_status = ERROR;
		print_error("pwd", NULL, 0, "error retrieving current directory");
		return ;
	}
	ft_printf("%s\n", cwd);
	free(cwd);
}
