/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tseche <tseche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 12:23:11 by rcompain          #+#    #+#             */
/*   Updated: 2026/03/06 19:29:52 by tseche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/mini_shell.h"

/**
 * This function opens the file descriptor for output redirection.
 */
void	open_fd_out(t_data *shell, t_cmd *cmd, t_ast_out *out)
{
	int	fd;

	if (out->overwrite == true)
		fd = open(out->output, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		fd = open(out->output, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		shell->error_status = ERROR;
		print_error("fd", out->output, 0, "invalid");
		return ;
	}
	cmd->fd_out = fd;
	cmd->redir_out = true;
}

/**
 * This function opens the file descriptor for input redirection.
 */
void	open_fd_in(t_data *shell, t_cmd *cmd, t_ast_in *in)
{
	int	fd;

	fd = open(in->input, O_RDONLY);
	if (fd == -1)
	{
		shell->error_status = ERROR;
		print_error("fd", in->input, 0, "invalid");
		return ;
	}
	cmd->fd_in = fd;
	cmd->redir_in = true;
}
