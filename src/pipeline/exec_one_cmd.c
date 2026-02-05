/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_one_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 13:50:03 by rcompain          #+#    #+#             */
/*   Updated: 2026/02/04 15:34:32 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/mini_shell.h"
#include <sys/wait.h>

static void	child_process_one_cmd(t_data *shell, t_cmd *cmd)
{
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

t_cmd	*exec_one_cmd(t_data *shell, t_cmd *cmd)
{
	int	pid;
	int	find;
	int	status;

	ft_printf("DEBUG exec_one_cmd: cmd=%p, cmd->args=%p\n", cmd, cmd->args);
	if (cmd->args && cmd->args[0])
		ft_printf("DEBUG: cmd->args[0]=%s\n", cmd->args[0]);
	if (cmd->is_builtin == true)
		dispatch_builtins(shell, cmd);
	else
	{
		find = find_path(shell, cmd->args);
		if (find == -1)
			return (NULL);
		pid = fork();
		if (pid == 0)
			child_process_one_cmd(shell, cmd);
		waitpid(pid, &status, 0);
		get_exit_status(shell, status);
	}
	return (cmd);
}
