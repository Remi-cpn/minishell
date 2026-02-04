/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 10:22:36 by rcompain          #+#    #+#             */
/*   Updated: 2026/02/04 14:33:44 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/mini_shell.h"
#include <fcntl.h>
#include <unistd.h>

void	get_exit_status(t_data *shell, int status)
{
	if (WIFEXITED(status))
		shell->exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		shell->exit_status = 128 + WTERMSIG(status);
	else
		shell->exit_status = ERROR;
}

void	dispatch_builtins(t_data *shell, t_cmd *cmd)
{
	ft_printf("DEBUG: dispatch_builtins called\n");
	if (!cmd || !cmd->args || !cmd->args[0])
		return ;
	ft_printf("DEBUG: cmd->args[0] = %s|\n", cmd->args[0]);
	if (ft_strncmp(cmd->args[0], "echo", 4) == 0)
		echo_cmd(shell, cmd->args);
	else if (ft_strncmp(cmd->args[0], "exit", 5) == 0)
		exit_cmd(shell, cmd->args);
	else if (ft_strncmp(cmd->args[0], "env", 4) == 0)
		env_cmd(shell, cmd->args);
	else if (ft_strncmp(cmd->args[0], "pwd", 4) == 0)
		pwd_cmd(shell, cmd->args);
	else if (ft_strncmp(cmd->args[0], "cd", 3) == 0)
		cd_cmd(shell, cmd->args);
	else if (ft_strncmp(cmd->args[0], "export", 7) == 0)
		export_cmd(shell, cmd->args);
	else if (ft_strncmp(cmd->args[0], "unset", 6) == 0)
		unset_cmd(shell, cmd->args);
}
