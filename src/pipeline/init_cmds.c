/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 11:02:39 by rcompain          #+#    #+#             */
/*   Updated: 2026/03/09 11:35:53 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/mini_shell.h"

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
		args = ft_freenull(args);
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

static void	set_cmd_defaults(t_data *shell, t_cmd *cmds, int *j)
{
	int	i;

	i = 0;
	while (i < shell->nbr_cmd + 1)
	{
		cmds[i].fd_in = STDIN_FILENO;
		cmds[i].fd_out = STDOUT_FILENO;
		cmds[i].redir_in = false;
		cmds[i].redir_out = false;
		cmds[i].last_cmd = false;
		cmds[i].next_and = false;
		cmds[i].next_or = false;
		cmds[i].is_builtin = false;
		i++;
	}
	*j = 0;
}

static void	init_cmd(t_data *shell, t_cmd *cmd, t_ast *ast_cmd)
{
	t_ast_cmd		*cmd_ast;
	t_ast_heredoc	*heredoc;

	if (ast_cmd->kind == CMD)
	{
		cmd_ast = (t_ast_cmd *)ast_cmd;
		cmd->is_builtin = is_builtins(cmd_ast);
		if (cmd_ast->name)
			cmd->args = init_args(cmd_ast);
		if (!cmd->args)
			call_to_exit(shell, ERR_ALLOC, NULL);
	}
	else if (ast_cmd->kind == HEREDOC)
	{
		heredoc = (t_ast_heredoc *)ast_cmd;
		open_fd_heredoc(shell, cmd, heredoc);
	}
	else if (ast_cmd->kind == SUBSHELL)
		cmd->subshell = ((t_ast_subshell *)ast_cmd)->inter;
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

	cmds = ft_calloc(shell->nbr_cmd + 1, sizeof(t_cmd));
	shell->cmds = cmds;
	set_cmd_defaults(shell, cmds, &i);
	tmp = *ast;
	while (cmds && shell->error_status != ERROR && tmp)
	{
		if (tmp->kind == CMD || tmp->kind == HEREDOC || tmp->kind == SUBSHELL)
			init_cmd(shell, &cmds[i], tmp);
		else if (tmp->kind == IN)
			open_fd_in(shell, &cmds[i], (t_ast_in *)tmp);
		else if (tmp->kind == OUT)
			open_fd_out(shell, &cmds[i], (t_ast_out *)tmp);
		else if (tmp->kind == OR || tmp->kind == AND || tmp->kind == END)
			init_or_and_end(&cmds[i], tmp->kind);
		if (tmp->kind != CMD && tmp->kind != HEREDOC
			&& tmp->kind != IN && tmp->kind != OUT && tmp->kind != SUBSHELL)
		{
			print_cmd(&cmds[i], i);
			i++;
		}
		tmp = tmp->next;
	}
	if (shell->nbr_cmd == 0 && i != 0)
		shell->nbr_cmd++;
	ft_printf("Nombre de cmds dans init_cmds: %d\n", shell->nbr_cmd);
	return (cmds);
}
