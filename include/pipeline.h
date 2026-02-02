/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 09:38:56 by rcompain          #+#    #+#             */
/*   Updated: 2026/02/01 18:11:43 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPELINE_H
# define PIPELINE_H

# include "mini_shell.h"
# include <fcntl.h>

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
}	t_cmd;

/** Functions */
t_cmd	*init_cmds(t_data *shell, t_ast **ast);
void	child_process(t_data *pipex, char **cmd, int i);

void	open_fd_heredoc(t_data *shell, t_cmd *cmd, t_ast_heredoc *heredoc);
void	open_fd_out(t_data *shell, t_cmd *cmd, t_ast_out *out);
void	open_fd_in(t_data *shell, t_cmd *cmd, t_ast_in *in);

int		test_path(t_data *shell, char *path, char **paths, char **cmd);
int		find_path(t_data *shell, char **cmd);

#endif