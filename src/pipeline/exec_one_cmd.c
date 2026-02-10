/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_one_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 13:50:03 by rcompain          #+#    #+#             */
/*   Updated: 2026/02/10 16:31:02 by rcompain         ###   ########.fr       */
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
	fprintf(stderr, "RUN pid=%d cmd=%s\n", getpid(), cmd->args[0]);
	execve(shell->cmd_path, cmd->args, shell->env);
	exit_prog(shell, ERR_CMD_NOT_FOUND);
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
		dispatch_builtins(shell, cmd);
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
		get_exit_status(shell, status);
		init_signals_prompt();
	}
	return (cmd);
}
