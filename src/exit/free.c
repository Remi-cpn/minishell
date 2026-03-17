/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tseche <tseche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 18:27:19 by rcompain          #+#    #+#             */
/*   Updated: 2026/03/12 11:09:47 by tseche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/mini_shell.h"

static void	free_kind(t_ast_type kind, t_ast *current)
{
	if (kind == CMD)
		free(((t_ast_cmd *)current)->name);
	if (kind == CMD)
		free_array(((t_ast_cmd *)current)->args);
	else if (kind == IN)
		free(((t_ast_in *)current)->input);
	else if (kind == OUT)
		free(((t_ast_out *)current)->output);
	else if (kind == HEREDOC)
		free(((t_ast_heredoc *)current)->del);
	else if (kind == SUBSHELL)
		free_ast(((t_ast_subshell *)current)->inter);
}

/** This function frees the memory allocated for the AST.
 * It traverses the AST and frees the memory for each node based on its type.
 */
void	free_ast(t_ast **ast)
{
	t_ast	*current;
	t_ast	*next;

	if (!ast)
		return ;
	current = *ast;
	while (current && (current->kind != END || current->next))
	{
		next = current->next;
		free_kind(current->kind, current);
		free(current);
		current = next;
	}
	free(current);
	free(ast);
}

/**
 * This function frees the memory allocated for an array of strings.
 */
void	free_array(char **s)
{
	int	i;

	i = 0;
	if (!s)
		return ;
	if (!*s)
	{
		free(s);
		return ;
	}
	while (s[i])
	{
		s[i] = ft_freenull(s[i]);
		i++;
	}
	s = ft_freenull(s);
}

/** 
 * This function frees the memory allocated for the command structures.
 */
void	free_cmds(t_data *shell)
{
	int	i;

	i = 0;
	if (shell->cmds)
	{
		while (i < shell->nbr_cmd)
		{
			free_array(shell->cmds[i].args);
			i++;
		}
		shell->cmds = ft_freenull(shell->cmds);
	}
	shell->nbr_cmd = 1;
	if (shell->cmd_path)
		shell->cmd_path = ft_freenull(shell->cmd_path);
}

void	reset_line(t_data *shell)
{
	if (g_exit_flag > 1)
		shell->error_status = g_exit_flag;
	g_exit_flag = 0;
	free_cmds(shell);
	if (shell->error_status < SUCCES)
		shell->error_status = ERROR;
	shell->last_error_status = shell->error_status;
	shell->error_status = SUCCES;
}
