/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 10:22:36 by rcompain          #+#    #+#             */
/*   Updated: 2026/02/24 16:29:58 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/mini_shell.h"
#include <fcntl.h>
#include <unistd.h>

void	error_pipeline(t_data *shell, char *msg, int error_status)
{
	print_error(msg, NULL, 0, NULL);
	shell->exit_status = error_status;
}

bool	is_builtins(t_ast_cmd	*cmd)
{
	if (!cmd || !cmd->name)
		return (false);
	if (ft_strncmp(cmd->name, "echo", 5) == 0)
		return (true);
	else if (ft_strncmp(cmd->name, "exit", 5) == 0)
		return (true);
	else if (ft_strncmp(cmd->name, "env", 4) == 0)
		return (true);
	else if (ft_strncmp(cmd->name, "pwd", 4) == 0)
		return (true);
	else if (ft_strncmp(cmd->name, "cd", 3) == 0)
		return (true);
	else if (ft_strncmp(cmd->name, "export", 7) == 0)
		return (true);
	else if (ft_strncmp(cmd->name, "unset", 6) == 0)
		return (true);
	return (false);
}

/**
 * This function retrieves the exit status of a child process and updates
 * the shell's exit status accordingly.
 */
void	get_exit_status(t_data *shell, int status)
{
	if (WIFEXITED(status))
		shell->exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		shell->exit_status = 128 + WTERMSIG(status);
	else
		shell->exit_status = ERROR;
}


/**
 * This function dispatches the built-in commands.
 */
void	dispatch_builtins(t_data *shell, t_cmd *cmd)
{
	if (!cmd || !cmd->args || !cmd->args[0])
		return ;
	//ft_printf("Dispatching built-in command: %s\n", cmd->args[0]);
	if (ft_strncmp(cmd->args[0], "echo", 4) == 0)
		echo_cmd(shell, cmd->args);
	else if (ft_strncmp(cmd->args[0], "exit", 4) == 0)
		exit_cmd(shell, cmd->args);
	else if (ft_strncmp(cmd->args[0], "env", 3) == 0)
		env_cmd(shell, cmd->args);
	else if (ft_strncmp(cmd->args[0], "pwd", 3) == 0)
		pwd_cmd(shell, cmd->args);
	else if (ft_strncmp(cmd->args[0], "cd", 2) == 0)
		cd_cmd(shell, cmd->args);
	else if (ft_strncmp(cmd->args[0], "export", 6) == 0)
		export_cmd(shell, cmd->args);
	else if (ft_strncmp(cmd->args[0], "unset", 5) == 0)
		unset_cmd(shell, cmd->args);
}
