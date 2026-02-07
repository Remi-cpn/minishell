/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 11:02:39 by rcompain          #+#    #+#             */
/*   Updated: 2026/02/07 18:18:44 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/mini_shell.h"

static bool	is_builtins(t_ast_cmd	*cmd)
{
	if (!cmd || !cmd->name)
		return (false);
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
		ft_freenull(args);
	i = 0;
	while (args && ast_cmd->args[i])
	{
		args[i + 1] = ft_strdup(ast_cmd->args[i], 0);
		if (!args[i + 1])
			free_array(args);
		i++;
	}
	return (args);
}

static void	init_or_and_end(t_cmd *cmd, int kind)
{
	if (kind == OR)
		cmd->next_or = true;
	else if (kind == AND)
		cmd->next_and = true;
	cmd->last_cmd = true;
}

static void	init_cmd(t_data *shell, t_cmd *cmd, t_ast_cmd	*ast_cmd)
{
	cmd->fd_in = STDIN_FILENO;
	cmd->fd_out = STDOUT_FILENO;
	cmd->redir_in = false;
	cmd->redir_out = false;
	cmd->last_cmd = false;
	cmd->next_and = false;
	cmd->next_or = false;
	cmd->is_builtin = is_builtins(ast_cmd);
	if (ast_cmd->name)
		cmd->args = init_args(ast_cmd);
	if (!cmd->args)
		call_to_exit(shell, ERR_ALLOC, NULL);
}

/**
 * This function initializes the command structures based on the AST.
 * It iterates through the AST and sets up the command structures.
 * It also handles the file descriptors for input and output redirection,
 * as well as the logic for AND and OR operators between commands.
 * Finally, it returns the array of initialized command structures.
 */
t_cmd	*init_cmds(t_data *shell, t_ast **ast)
{
	t_cmd	*cmds;
	int		i;
	t_ast	*tmp;

	i = -1;
	cmds = ft_calloc(shell->nbr_cmd + 1, sizeof(t_cmd));
	tmp = *ast;
	while (cmds && shell->exit_status != ERROR && tmp && i < shell->nbr_cmd)
	{
		if (tmp->kind == CMD)
			init_cmd(shell, &cmds[++i], (t_ast_cmd *)tmp);
		else if (tmp->kind == IN)
			open_fd_in(shell, &cmds[i], (t_ast_in *)tmp);
		else if (tmp->kind == HEREDOC)
			open_fd_heredoc(shell, &cmds[i], (t_ast_heredoc *)tmp, i);
		else if (tmp->kind == OUT)
			open_fd_out(shell, cmds, (t_ast_out *)tmp, i);
		else if (tmp->kind == OR || tmp->kind == AND || tmp->kind == END)
			init_or_and_end(&cmds[i], tmp->kind);
		tmp = tmp->next;
		print_cmd(&cmds[i], i);
	}
	ft_printf("Total cmds initialized: %d\n", i + 1);
	ft_printf("Nombre de cmds dans init_cmds: %d\n", shell->nbr_cmd);
	shell->cmds = cmds;
	return (cmds);
}
