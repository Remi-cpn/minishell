/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 10:22:36 by rcompain          #+#    #+#             */
/*   Updated: 2026/03/19 10:24:00 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/mini_shell.h"
#include <fcntl.h>
#include <signal.h>
#include <unistd.h>

void	init_or_and_end(t_cmd *cmd, int kind)
{
	if (kind == OR)
		cmd->next_or = true;
	else if (kind == AND)
		cmd->next_and = true;
	cmd->last_cmd = true;
}

int	error_pipeline(t_data *shell, char *msg, int error_status, int res)
{
	print_error(msg, NULL, 0, NULL);
	shell->error_status = error_status;
	return (res);
}

bool	is_builtins(char *name)
{
	if (!name)
		return (false);
	if (ft_strncmp(name, "echo", 5) == 0)
		return (true);
	else if (ft_strncmp(name, "exit", 5) == 0)
		return (true);
	else if (ft_strncmp(name, "env", 4) == 0)
		return (true);
	else if (ft_strncmp(name, "pwd", 4) == 0)
		return (true);
	else if (ft_strncmp(name, "cd", 3) == 0)
		return (true);
	else if (ft_strncmp(name, "export", 7) == 0)
		return (true);
	else if (ft_strncmp(name, "unset", 6) == 0)
		return (true);
	return (false);
}

/**
 * This function retrieves the exit status of a child process and updates
 * the shell's exit status accordingly.
 */
void	get_error_status(t_data *shell, int status)
{
	if (WIFEXITED(status))
		shell->error_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		write(1, "\n", 1);
		shell->error_status = 128 + WTERMSIG(status);
		if (shell->error_status == 141)
			shell->error_status = 0;
	}
	else
		shell->error_status = ERROR;
}

/**
 * This function dispatches the built-in commands.
 */
void	dispatch_builtins(t_data *shell, t_cmd *cmd)
{
	if (!cmd || !cmd->args || !cmd->args[0])
		return ;
	if (shell->is_child == true)
		signal(SIGPIPE, SIG_IGN);
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
