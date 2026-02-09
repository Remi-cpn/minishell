/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 12:23:11 by rcompain          #+#    #+#             */
/*   Updated: 2026/02/10 00:06:53 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/mini_shell.h"

static int	heredoc_to_pipe(t_ast_heredoc *h)
{
	int		fd[2];
	char	*line;

	if (pipe(fd) == -1)
		return (-1);
	while (true)
	{
		line = readline("> ");
		if (!line || ft_strncmp(line, h->del, ft_strlen(h->del)) == 0)
		{
			free(line);
			break ;
		}
		ft_putendl_fd(line, fd[1]);
		free(line);
	}
	close(fd[1]);
	return (fd[0]);
}

void	open_fd_heredoc(t_data *shell, t_cmd *cmd, t_ast_heredoc *heredoc)
{
	int	fd;

	fd = heredoc_to_pipe(heredoc);
	if (fd == -1)
	{
		shell->exit_status = ERROR;
		print_error("fd", heredoc->del, 0, "invalid");
		return ;
	}
	cmd->fd_in = fd;
	cmd->redir_in = true;
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
