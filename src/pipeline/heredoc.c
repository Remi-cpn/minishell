/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 19:27:43 by tseche            #+#    #+#             */
/*   Updated: 2026/03/19 10:16:29 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/mini_shell.h"

static void	handler_heredoc(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	g_exit_flag = 1;
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

static void	heredoc_child_process(
	t_data *shell,
	t_ast_heredoc *h,
	int fd[2],
	int expand)
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
		if (expand)
			line = expand_all_heredoc(line, shell);
		if (!line)
			break ;
		ft_putendl_fd(line, fd[1]);
		free(line);
	}
	close(fd[1]);
	free_ast(shell->ast);
	free_cmds(shell);
	if (g_exit_flag)
		exit_prog(shell, 130);
	exit_prog(shell, SUCCES);
}

static int	heredoc_pipeline(t_data *shell, t_ast_heredoc *h, int expand)
{
	int	fd[2];
	int	pid;
	int	status;

	if (pipe(fd) == -1)
		return (error_pipeline(shell, "pipe error", ERR_PIPE, -1));
	pid = fork();
	if (pid == -1)
	{
		close(fd[0]);
		close(fd[1]);
		return (error_pipeline(shell, "fork", ERR_FORK, -1));
	}
	init_signals_parent();
	if (pid == 0)
		heredoc_child_process(shell, h, fd, expand);
	close(fd[1]);
	waitpid(pid, &status, 0);
	get_error_status(shell, status);
	init_signals_prompt();
	return (fd[0]);
}

void	open_fd_heredoc(t_data *shell, t_cmd *cmd, t_ast_heredoc *heredoc)
{
	int	fd;
	int	expand;

	if (ft_strchr(heredoc->del, '\'') || ft_strchr(heredoc->del, '"'))
		expand = 0;
	else
		expand = 1;
	heredoc->del = dequote((char *[2]){[0] = heredoc->del, [1] = NULL});
	fd = heredoc_pipeline(shell, heredoc, expand);
	if (fd == -1)
	{
		shell->error_status = ERROR;
		print_error("fd", heredoc->del, 0, "invalid");
		return ;
	}
	cmd->fd_in = fd;
	cmd->redir_in = true;
}
