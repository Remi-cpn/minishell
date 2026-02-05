/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 18:27:19 by rcompain          #+#    #+#             */
/*   Updated: 2026/02/04 18:29:58 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/mini_shell.h"

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
	if (ast)
		free(ast);
}

void	free_array(char **s)
{
	int	i;

	i = 0;
	while (s && s[i])
		ft_freenull(s[i++]);
	if (s)
		ft_freenull(s);
}

void	free_cmds(t_data *shell, t_cmd *cmds)
{
	int	i;

	i = 0;
	if (cmds)
	{
		while (cmds[i].args)
		{
			free_array(cmds[i].args);
			cmds[i].args = NULL;
			i++;
		}
		ft_freenull(cmds);
		cmds = NULL;
	}
	shell->nbr_cmd = 0;
}

void	free_env(char **env)
{
	int	i;

	if (!env)
		return ;
	i = 0;
	while (env[i])
	{
		free(env[i]);
		env[i] = NULL;
		i++;
	}
	free(env);
}