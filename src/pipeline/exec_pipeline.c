/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 11:26:17 by rcompain          #+#    #+#             */
/*   Updated: 2026/02/02 14:33:34 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/mini_shell.h"

static void	closed_fds(t_cmd *cmd, int prev_read, int pipefd[2])
{
	if (cmd->redir_in == true)
		close(cmd->fd_in);
	if (prev_read != -1)
		close(prev_read);
	if (cmd->redir_out == true)
		close(cmd->fd_out);
	else if (cmd->last_cmd == false)
	{
		close(pipefd[0]);
		close(pipefd[1]);
	}
}

static void	child_process(t_data *shell, t_cmd *cmd, int prev_read,
				int pipefd[2])
{
	int	find;
	int	j;

	find = find_path(shell, cmd->args);
	if (find == FAILURE)
		exit_prog(shell, shell->exit_status);
	if (cmd->redir_in == true)
		dup2(cmd->fd_in, STDIN_FILENO);
	else if (prev_read != -1)
		dup2(prev_read, STDIN_FILENO);
	if (cmd->redir_out == true)
		dup2(cmd->fd_out, STDOUT_FILENO);
	else if (cmd->last_cmd == false)
		dup2(pipefd[1], STDOUT_FILENO);
	closed_fds(cmd, prev_read, pipefd);
	if (cmd->is_builtin == true)
	{
		dispatch_builtins(shell, NULL);
		exit_prog(shell, shell->exit_status);
	}
	execve(shell->cmd_path, cmd->args, shell->env);
	exit_prog(shell, ERROR);
}

void	exec_pipeline(t_data *shell, t_cmd *cmds, pid_t *pid)
{
	int	i;
	int	prev_read;
	int	pipefd[2];
	int	status;

	i = -1;
	prev_read = -1;
	while (++i < shell->nbr_cmd)
	{
		if (i < shell->nbr_cmd - 1)
			pipe(pipefd);
		pid[i] = fork();
		if (pid[i] == CHILD)
			child_process(shell, &cmds[i], prev_read, pipefd);
		if (prev_read != -1)
			close(prev_read);
		if (cmds[i].last_cmd == false)
		{
			close(pipefd[1]);
			prev_read = pipefd[0];
		}
		else
			prev_read = -1;
	}
	i = 0;
	while (i < shell->nbr_cmd)
		waitpid(pid[i++], &status, 0);
	get_exit_status(shell, status);
}
