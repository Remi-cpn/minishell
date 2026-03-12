/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 12:23:11 by rcompain          #+#    #+#             */
/*   Updated: 2026/03/12 03:52:28 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/mini_shell.h"

/**
 * This function opens the file descriptor for output redirection.
 */
void	open_fd_out(t_data *shell, t_cmd *cmd, t_ast_out *out)
{
	int		fd;
	char	*name;

	(void)shell;
	name = NULL;
	if (cmd->args)
		name = cmd->args[0];
	if (out->overwrite == true)
		fd = open(out->output, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		fd = open(out->output, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		cmd->redir_error = true;
		print_error(name, out->output, 0, "Permission denied");
		return ;
	}
	if (cmd->fd_out != STDOUT_FILENO)
		close(cmd->fd_out);
	cmd->fd_out = fd;
	cmd->redir_out = true;
}

/**
 * This function opens the file descriptor for input redirection.
 */
void	open_fd_in(t_data *shell, t_cmd *cmd, t_ast_in *in)
{
	int		fd;
	char	*name;

	(void)shell;
	name = NULL;
	if (cmd->args)
		name = cmd->args[0];
	fd = open(in->input, O_RDONLY);
	if (fd == -1)
	{
		cmd->redir_error = true;
		print_error(name, in->input, 0, "Permission denied");
		return ;
	}
	if (cmd->fd_in != STDIN_FILENO)
		close(cmd->fd_in);
	cmd->fd_in = fd;
	cmd->redir_in = true;
}
