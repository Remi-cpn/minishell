/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: von <von@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 19:27:43 by tseche            #+#    #+#             */
/*   Updated: 2026/03/08 15:30:30 by von              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/mini_shell.h"

static void	handler_heredoc(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	close(STDIN_FILENO);
}

void	init_signals_heredoc(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_handler = handler_heredoc;
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	sa.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa, NULL);
}

static void	heredoc_child_process(t_data *shell, t_ast_heredoc *h, int fd[2])
{
	char	*line;

	init_signals_heredoc();
	close(fd[0]);
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
	free_ast(shell->ast);
	free_cmds(shell);
	exit_prog(shell, SUCCES);
}

static int	heredoc_pipeline(t_data *shell, t_ast_heredoc *h)
{
	int		fd[2];
	int		pid;
	int		status;

	if (pipe(fd) == -1)
	{
		error_pipeline(shell, "pipe error", ERR_PIPE);
		return (-1);
	}
	pid = fork();
	if (pid == -1)
	{
		error_pipeline(shell, "fork", ERR_FORK);
		close(fd[0]);
		close(fd[1]);
		return (-1);
	}
	init_signals_parent();
	if (pid == 0)
		heredoc_child_process(shell, h, fd);
	close(fd[1]);
	waitpid(pid, &status, 0);
	get_error_status(shell, status);
	init_signals_prompt();
	return (fd[0]);
}

void	open_fd_heredoc(t_data *shell, t_cmd *cmd, t_ast_heredoc *heredoc)
{
	int	fd;

	heredoc->del = expand_all_heredoc(heredoc->del, shell);
	fd = heredoc_pipeline(shell, heredoc);
	if (fd == -1)
	{
		shell->error_status = ERROR;
		print_error("fd", heredoc->del, 0, "invalid");
		return ;
	}
	cmd->fd_in = fd;
	cmd->redir_in = true;
}
