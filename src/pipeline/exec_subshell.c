/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_subshell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tseche <tseche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 11:43:56 by rcompain          #+#    #+#             */
/*   Updated: 2026/03/17 14:11:20 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/mini_shell.h"

static void	setup_subshell_fds(t_cmd *cmd)
{
	if (cmd->fd_in != STDIN_FILENO)
	{
		dup2(cmd->fd_in, STDIN_FILENO);
		close(cmd->fd_in);
		cmd->fd_in = STDIN_FILENO;
	}
	if (cmd->fd_out != STDOUT_FILENO)
	{
		dup2(cmd->fd_out, STDOUT_FILENO);
		close(cmd->fd_out);
		cmd->fd_out = STDOUT_FILENO;
	}
}

static void	child_process_subshell(t_data *shell, t_cmd *cmd)
{
	int		save_nbr_cmd;
	t_ast	**inter_ast;

	init_signals_child();
	setup_subshell_fds(cmd);
	close_cmds_fds(shell);
	inter_ast = cmd->subshell;
	save_nbr_cmd = cmd->nbr_cmd_subshell;
	free_cmds(shell);
	shell->nbr_cmd = save_nbr_cmd;
	shell->last_error_status = shell->error_status;
	if (inter_ast)
		exec(shell, inter_ast);
	free_ast(shell->ast);
	exit_prog(shell, shell->error_status);
}

void	exec_subshell_child(t_data *shell, t_cmd *cmd)
{
	t_ast	**inner;
	int		nbr;

	inner = cmd->subshell;
	nbr = cmd->nbr_cmd_subshell;
	free_cmds(shell);
	shell->nbr_cmd = nbr;
	shell->last_error_status = shell->error_status;
	exec(shell, inner);
	free_ast(shell->ast);
	exit_prog(shell, shell->error_status);
}

t_cmd	*exec_subshell(t_data *shell, t_cmd *cmd)
{
	int	pid;
	int	status;

	init_signals_parent();
	pid = fork();
	if (pid == 0)
	{
		shell->is_child = true;
		child_process_subshell(shell, cmd);
	}
	if (cmd->fd_in != STDIN_FILENO)
		close(cmd->fd_in);
	if (cmd->fd_out != STDOUT_FILENO)
		close(cmd->fd_out);
	waitpid(pid, &status, 0);
	get_error_status(shell, status);
	init_signals_prompt();
	return (cmd);
}
