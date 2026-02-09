/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tseche <tseche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 18:27:19 by rcompain          #+#    #+#             */
/*   Updated: 2026/02/09 11:15:09 by tseche           ###   ########.fr       */
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
		ft_freenull(s[i++]);
	ft_freenull(s);
}

/** 
 * This function frees the memory allocated for the command structures.
 */
void	free_cmds(t_data *shell, t_cmd *cmds)
{
	int	i;

	i = 0;
	if (cmds)
	{
		while (i < shell->nbr_cmd)
		{
			free_array(cmds[i].args);
			cmds[i].args = NULL;
			i++;
		}
		ft_freenull(cmds);
		cmds = NULL;
	}
	shell->nbr_cmd = 0;
	if (shell->cmd_path)
	{
		ft_freenull(shell->cmd_path);
		shell->cmd_path = NULL;
	}
}
