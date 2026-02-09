/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 18:27:19 by rcompain          #+#    #+#             */
/*   Updated: 2026/02/09 16:32:57 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/mini_shell.h"

/** This function frees the memory allocated for the AST.
 * It traverses the AST and frees the memory for each node based on its type.
 */
void	free_ast(t_ast **ast)
{
	t_ast	*current;
	t_ast	*next;

	if (!ast || !*ast)
		return ;
	current = *ast;
	while (current)
	{
		next = current->next;
		if (current->kind == CMD)
		{
			free(((t_ast_cmd *)current)->name);
			free_array(((t_ast_cmd *)current)->args);
		}
		else if (current->kind == IN)
			free(((t_ast_in *)current)->input);
		else if (current->kind == OUT)
			free(((t_ast_out *)current)->output);
		else if (current->kind == HEREDOC)
			free(((t_ast_heredoc *)current)->del);
		free(current);
		current = next;
	}
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
	shell->nbr_cmd = 0;
	if (shell->cmd_path)
		shell->cmd_path = ft_freenull(shell->cmd_path);
}

void	reset_line(t_data *shell)
{
	free_cmds(shell);
	shell->exit_status = SUCCES;
}
