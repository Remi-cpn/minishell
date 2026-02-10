/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 09:38:56 by rcompain          #+#    #+#             */
/*   Updated: 2026/02/10 09:54:55 by rcompain         ###   ########.fr       */
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
}	t_cmd;

/** Functions */
void	exec(t_data *shell, t_ast **ast);
t_cmd	*init_cmds(t_data *shell, t_ast **ast);
t_cmd	*exec_one_cmd(t_data *shell, t_cmd *cmd);
t_cmd	*exec_pipeline(t_data *shell, t_cmd *cmds, pid_t *pid);

void	open_fd_heredoc(t_data *shell, t_cmd *cmd, t_ast_heredoc *heredoc);
void	open_fd_out(t_data *shell, t_cmd *cmd, t_ast_out *out);
void	open_fd_in(t_data *shell, t_cmd *cmd, t_ast_in *in);

int		find_path(t_data *shell, char **cmd);
void	dispatch_builtins(t_data *shell, t_cmd *cmd);
void	get_exit_status(t_data *shell, int status);
bool	is_builtins(t_ast_cmd	*cmd);
void	error_pipeline(t_data *shell, char *msg, int error_status);

#endif
