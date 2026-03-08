/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: von <von@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 11:26:17 by rcompain          #+#    #+#             */
/*   Updated: 2026/03/08 15:25:39 by von              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/mini_shell.h"
#include <unistd.h>

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

	find = FAILURE;
	init_signals_child();
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
		dispatch_builtins(shell, cmd);
	else
		find = find_path(shell, cmd->args);
	if (find == SUCCES)
		execve(shell->cmd_path, cmd->args, shell->env);
	close(cmd->fd_out);
	close(cmd->fd_in);
	exit_prog(shell, shell->error_status);
}

static int	pipeline(t_data *shell, t_cmd *cmd, int pid, int prev_read)
{
	int	pipefd[2];

	if (cmd->last_cmd == false)
	{
		if (pipe(pipefd) == -1)
		{
			error_pipeline(shell, "pipe error", ERR_PIPE);
			return (-1);
		}
	}
	pid = fork();
	if (pid == -1)
		error_pipeline(shell, "fork", ERR_FORK);
	else if (pid == CHILD)
	{
		cmd->args = expansion(cmd->args, shell);
		//if (!cmd->args)
		//		do somthing;
		free(shell->pid_adr);
		child_process(shell, cmd, prev_read, pipefd);
	}
	if (prev_read != -1)
		close(prev_read);
	if (cmd->last_cmd == false && pid != -1)
	{
		close(pipefd[1]);
		return (pipefd[0]);
	}
	return (-1);
}

/**
 * This function executes a series of commands in a pipeline. It handles the
 * creation of pipes, forking of child processes, and execution of commands.
 * It also manages the file descriptors for input and output redirection.
 * Finally, it waits for all child processes to finish and retrieves the exit
 * status of the last command executed.
 */
t_cmd	*exec_pipeline(t_data *shell, t_cmd *cmds, pid_t *pid)
{
	int	i;
	int	j;
	int	prev_read;
	int	status;

	i = 0;
	prev_read = -1;
	shell->pid_adr = pid;
	init_signals_parent();
	while (prev_read != -1 || i == 0)
	{
		prev_read = pipeline(shell, &cmds[i], pid[i], prev_read);
		i++;
	}
	j = 0;
	while (j < i)
		waitpid(pid[j++], &status, 0);
	get_error_status(shell, status);
	init_signals_prompt();
	return (cmds + i - 1);
}
