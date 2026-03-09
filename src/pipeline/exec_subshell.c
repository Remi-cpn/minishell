/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_subshell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 11:43:56 by rcompain          #+#    #+#             */
/*   Updated: 2026/03/09 13:30:45 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/mini_shell.h"

static void	find_node_subshell(t_ast **save_ast)
{
	t_ast	*node;

	node = *save_ast;
	while (node && node->kind != SUBSHELL)
		node = node->next;
	if (node)
		((t_ast_subshell *)node)->inter = NULL;
}

static void	child_process_subshell(t_data *shell, t_cmd *cmd)
{
	t_cmd	*save_cmd;
	t_ast	**save_ast;

	init_signals_child();
	if (cmd->fd_in != STDIN_FILENO)
		dup2(cmd->fd_in, STDIN_FILENO);
	if (cmd->fd_out != STDOUT_FILENO)
		dup2(cmd->fd_out, STDOUT_FILENO);
	if (cmd->fd_in != STDIN_FILENO)
		close(cmd->fd_in);
	if (cmd->fd_out != STDOUT_FILENO)
		close(cmd->fd_out);
	save_cmd = shell->cmds;
	save_ast = shell->ast;
	find_node_subshell(save_ast);
	shell->nbr_cmd = cmd->nbr_cmd_subshell;
	exec(shell, cmd->subshell);
	free_ast(save_ast);
	free(save_cmd);
	write(1, "EXIT CHILD\n", 11);
	exit_prog(shell, shell->error_status);
}

t_cmd	*exec_subshell(t_data *shell, t_cmd *cmd)
{
	int	pid;
	int	status;

	init_signals_parent();
	pid = fork();
	if (pid == 0)
		child_process_subshell(shell, cmd);
	if (cmd->fd_in != STDIN_FILENO)
		close(cmd->fd_in);
	if (cmd->fd_out != STDOUT_FILENO)
		close(cmd->fd_out);
	waitpid(pid, &status, 0);
	get_error_status(shell, status);
	init_signals_prompt();
	return (cmd);
}
