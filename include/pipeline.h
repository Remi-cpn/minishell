/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tseche <tseche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 09:38:56 by rcompain          #+#    #+#             */
/*   Updated: 2026/03/17 14:54:03 by tseche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPELINE_H
# define PIPELINE_H

# include "mini_shell.h"
# include <fcntl.h>
# include <sys/wait.h>

# define FAILURE -1
# define CHILD 0

/** Struct */
typedef struct s_cmd
{
	char	**args;
	bool	is_builtin;
	int		fd_in;
	int		fd_out;
	bool	redir_in;
	bool	redir_out;
	bool	last_cmd;
	bool	next_or;
	bool	next_and;
	bool	redir_error;
	t_ast	**subshell;
	int		nbr_cmd_subshell;
}	t_cmd;

/** Functions */
void	exec(t_data *shell, t_ast **ast);
t_cmd	*init_cmds(t_data *shell, t_ast **ast);
t_cmd	*exec_one_cmd(t_data *shell, t_cmd *cmd);
t_cmd	*exec_pipeline(t_data *shell, t_cmd *cmds, pid_t *pid);
t_cmd	*exec_subshell(t_data *shell, t_cmd *cmd);
void	exec_subshell_child(t_data *shell, t_cmd *cmd);

void	open_fd_heredoc(t_data *shell, t_cmd *cmd, t_ast_heredoc *heredoc);
void	open_fd_out(t_data *shell, t_cmd *cmd, t_ast_out *out);
void	open_fd_in(t_data *shell, t_cmd *cmd, t_ast_in *in);

int		find_path(t_data *shell, char **cmd);
void	dispatch_builtins(t_data *shell, t_cmd *cmd);
void	get_error_status(t_data *shell, int status);
bool	is_builtins(char *name);
int		error_pipeline(t_data *shell, char *msg, int error_status, int error);
void	close_cmds_fds(t_data *shell);
void	init_or_and_end(t_cmd *cmd, int kind);

#endif
