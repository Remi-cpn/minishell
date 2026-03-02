/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_one_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 13:50:03 by rcompain          #+#    #+#             */
/*   Updated: 2026/02/28 10:54:07 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/mini_shell.h"
#include <sys/wait.h>

static void	child_process_one_cmd(t_data *shell, t_cmd *cmd)
{
	init_signals_child();
	if (cmd->fd_in != STDIN_FILENO)
		dup2(cmd->fd_in, STDIN_FILENO);
	if (cmd->fd_out != STDOUT_FILENO)
		dup2(cmd->fd_out, STDOUT_FILENO);
	if (cmd->fd_in != STDIN_FILENO)
		close(cmd->fd_in);
	if (cmd->fd_out != STDOUT_FILENO)
		close(cmd->fd_out);
	execve(shell->cmd_path, cmd->args, shell->env);
	exit_prog(shell, ERR_CMD_NOT_FOUND);
}

static void	builtins_process_one_cmd(t_data *shell, t_cmd *cmd)
{
	int	saved_in;
	int	saved_out;

	if (cmd->redir_in || cmd->redir_out)
	{
		saved_in = dup(STDIN_FILENO);
		saved_out = dup(STDOUT_FILENO);
		if (cmd->fd_in != STDIN_FILENO)
			dup2(cmd->fd_in, STDIN_FILENO);
		if (cmd->fd_out != STDOUT_FILENO)
			dup2(cmd->fd_out, STDOUT_FILENO);
		dispatch_builtins(shell, cmd);
		dup2(saved_in, STDIN_FILENO);
		dup2(saved_out, STDOUT_FILENO);
		close(saved_in);
		close(saved_out);
		if (cmd->fd_in != STDIN_FILENO)
			close(cmd->fd_in);
		if (cmd->fd_out != STDOUT_FILENO)
			close(cmd->fd_out);
	}
	else
		dispatch_builtins(shell, cmd);
}

/** This function executes a single command that is not part of a pipeline. It
 * handles built-in commands directly in the parent process, and for external
 * commands, it forks a child process to execute the command using execve.
 * After execution, it waits for the child process to finish and retrieves the
 * exit status.
 */
t_cmd	*exec_one_cmd(t_data *shell, t_cmd *cmd)
{
	int	pid;
	int	find;
	int	status;

	if (cmd->is_builtin == true)
		builtins_process_one_cmd(shell, cmd);
	else
	{
		find = find_path(shell, cmd->args);
		if (find == -1)
			return (cmd);
		init_signals_parent();
		pid = fork();
		if (pid == 0)
			child_process_one_cmd(shell, cmd);
		if (cmd->fd_in != STDIN_FILENO)
			close(cmd->fd_in);
		if (cmd->fd_out != STDOUT_FILENO)
			close(cmd->fd_out);
		waitpid(pid, &status, 0);
		get_error_status(shell, status);
		init_signals_prompt();
	}
	return (cmd);
}
