/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 11:02:39 by rcompain          #+#    #+#             */
/*   Updated: 2026/01/30 13:48:17 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/mini_shell.h"

static bool	is_builtins(t_ast_cmd	*cmd)
{
	if (ft_strncmp(cmd->name, "echo", 4) == 0)
		return (true);
	else if (ft_strncmp(cmd->name, "exit", 4) == 0)
		return (true);
	else if (ft_strncmp(cmd->name, "env", 3) == 0)
		return (true);
	else if (ft_strncmp(cmd->name, "pwd", 3) == 0)
		return (true);
	else if (ft_strncmp(cmd->name, "cd", 2) == 0)
		return (true);
	else if (ft_strncmp(cmd->name, "export", 6) == 0)
		return (true);
	else if (ft_strncmp(cmd->name, "unset", 5) == 0)
		return (true);
	return (false);
}

static char	**init_args(t_ast_cmd	*ast_cmd)
{
	int		count;
	int		i;
	char	**args;

	count = 0;
	while (ast_cmd->args[count])
		count++;
	args = ft_calloc(count + 2, sizeof(char *));
	if (!args)
		return (NULL);
	args[0] = ft_strdup(ast_cmd->name, 0);
	if (!args[0])
		return (NULL);
	i = 0;
	while (ast_cmd->args[i])
	{
		args[i + 1] = ft_strdup(ast_cmd->args[i], 0);
		if (!args[i + 1])
			return (NULL);
		i++;
	}
	return (args);
}

static void	init_cmd(t_cmd *cmd, t_ast_cmd	*ast_cmd)
{
	cmd->args = init_args(ast_cmd);
	cmd->fd_in = STDIN_FILENO;
	cmd->fd_out = STDOUT_FILENO;
	cmd->redir_in = false;
	cmd->redir_out = false;
	cmd->is_builtin = false;
}

t_cmd	*init_cmds(t_data *shell, t_ast **ast)
{
	t_cmd	*cmds;
	int		i;
	t_ast	*tmp;
	int		fd;

	i = -1;
	cmds = ft_calloc(shell->nbr_cmd + 1, sizeof(t_cmd));
	if (!cmds)
		return ;
	tmp = *ast;
	while (tmp)
	{
		if (tmp->kind == CMD)
		{
			init_cmd(&cmds[++i], (t_ast_cmd *)tmp);
			cmds[i].is_builtin = is_builtin((t_ast_cmd *)tmp);
		}
		else if (tmp->kind == IN)
			open_fd_in(&cmds[i], (t_ast_in *)tmp);
		else if (tmp->kind == HEREDOC)
			open_fd_herdoc(&cmds[i], (t_ast_heredoc *)tmp);
		else if (tmp->kind == OUT)
			open_fd_out(&cmds[i], (t_ast_out *)tmp);
		tmp = tmp->next;
	}
	return (cmds);
}
