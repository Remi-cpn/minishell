/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 12:23:11 by rcompain          #+#    #+#             */
/*   Updated: 2026/02/07 18:03:45 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/mini_shell.h"

// //fd = creation d'un heredoc
// if (fd == -1)
// {
// 	write(2, "fd: invalid\n", 12);
// 	cmd->fd_in = -1;
// 	return ;
// }
// cmd->fd_in = fd;
// cmd->redir_in = true;
void	open_fd_heredoc(t_data *shell, t_cmd *cmd, t_ast_heredoc *heredoc,
				int i)
{
	(void)heredoc;
	(void)cmd;
	(void)shell;
	(void)i;
}

/**
 * This function opens the file descriptor for output redirection.
 */
void	open_fd_out(t_data *shell, t_cmd *cmd, t_ast_out *out, int i)
{
	int	fd;

	if (out->overwrite == true)
		fd = open(out->output, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		fd = open(out->output, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		shell->exit_status = ERROR;
		print_error("fd", out->output, 0, "invalid");
		return ;
	}
	if (i >= 0)
	{
		cmd[i].fd_out = fd;
		cmd[i].redir_out = true;
	}
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
		shell->exit_status = ERROR;
		print_error("fd", in->input, 0, "invalid");
		return ;
	}
	cmd->fd_in = fd;
	cmd->redir_in = true;
}
