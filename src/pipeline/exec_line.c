/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 13:50:03 by rcompain          #+#    #+#             */
/*   Updated: 2026/02/02 14:34:13 by rcompain         ###   ########.fr       */
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

static void	exec_one_cmd(t_data *shell, t_cmd *cmd)
{
	int	pid;
	int	find;
	int	status;

	if (cmd->is_builtin == true)
		dispatch_builtins(shell, NULL); // choix a faire sur builins depuis cmd
	else
	{
		find = find_path(shell, cmd->args);
		if (find == -1)
			return ;
		pid = fork();
		if (pid == 0)
			child_process_one_cmd(shell, cmd);
		waitpid(pid, &status, 0);
		get_exit_status(shell, status);
	}
}

void	exec_line(t_data *shell, t_ast **ast)
{
	pid_t	*pid;
	t_cmd	*cmds;
	int		i;

	cmds = init_cmds(shell, ast);
	i = 0;
	if (shell->exit_status != ERROR && shell->nbr_cmd <= 1)
		exec_one_cmd(shell, &cmds[i]);
	else if (shell->exit_status != ERROR)
	{
		pid = ft_calloc(shell->nbr_cmd, sizeof(pid_t));
		if (!pid)
		{
			call_to_exit(shell, ERR_ALLOC, NULL);
			return ;
		}
		exec_pipeline(shell, cmds, pid);
	}
}
