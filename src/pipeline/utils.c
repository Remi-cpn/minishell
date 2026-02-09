/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 10:22:36 by rcompain          #+#    #+#             */
/*   Updated: 2026/02/10 00:31:22 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/mini_shell.h"
#include <fcntl.h>
#include <unistd.h>

bool	is_builtins(t_ast_cmd	*cmd)
{
	if (!cmd || !cmd->name)
		return (false);
	if (ft_strncmp(cmd->name, "echo", 4) == 0)
		return (true);
	else if (ft_strncmp(cmd->name, "exit", 4) == 0)
		return (true);
	else if (ft_strncmp(cmd->name, "env", 3) == 0)
		return (true);
	else if (ft_strncmp(cmd->name, "pwd", 3) == 0)
		return (true);
	else if (ft_strncmp(cmd->name, "cd", 2) == 0)
		return (true);
	else if (ft_strncmp(cmd->name, "export", 6) == 0)
		return (true);
	else if (ft_strncmp(cmd->name, "unset", 5) == 0)
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
	//Une fois plus de ' ' dans les args, on peut mettre +1 pour cmp jusqu'a '\0'
	if (!cmd || !cmd->args || !cmd->args[0])
		return ;
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
