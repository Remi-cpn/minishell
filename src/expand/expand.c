/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: von <von@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 12:48:42 by tseche            #+#    #+#             */
/*   Updated: 2026/02/28 07:08:00 by von              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/mini_shell.h"

char	*get_env_key(char *str, char **env)
{
	while (*env)
	{
		if (ft_strncmp(str, *env, ft_strchr(*env, '=') - *env) == 0)
			return (ft_strchr(*env, '=') + 1);
		env++;
	}
	return (NULL);
}

int	skip_pattern(char *str, char *p)
{
	char	*src;

	src = str;
	while (*str && ft_isoneof(*str, p) && str++)
		;
	return (str - src);
}

char	**join_dbchar(char **string, char **add, int **start, int *lenght)
{
	int		i;
	char	**tmp;

	i = 0;
	while (add[i])
	{
		if (string[**start])
			free(string[**start]);
		else if (i > *lenght)
		{
			tmp = string;
			string = ft_realloc(string, *lenght, *lenght * 2, sizeof(char *));
			free_array(tmp);
			if (!string)
				return (NULL);
			*lenght *= 2;
		}
		string[**start++] = add[i++];
	}
	return (string);
}

void	expandcmd(t_ast_cmd **ast, t_data *shell)
{
	char **args;
	int		i;

	(*ast)->name = expand_all((*ast)->name, shell);
	args = (*ast)->args;
	i = 0;
    while (args && args[i])
    {
        args[i] = expand_all(args[i], shell);
		i++;
    }
}

t_ast    **dispatch_expand(t_ast **node, t_data *shell)
{
	t_ast	*ast;

	if (!node)
		return (NULL);
	ast = *node;
	while (ast->kind != END)
	{
		if (ast->kind == CMD)
			expandcmd((t_ast_cmd **)&ast, shell);
		//enlever les quote plutot que expand;
		else if (ast->kind == HEREDOC)
			((t_ast_heredoc *)ast)->del = expand_all(((t_ast_heredoc *)ast)->del, shell);
		else if (ast->kind == OUT)
			((t_ast_out *)ast)->output = expand_all(((t_ast_out *)ast)->output, shell);
		else if (ast->kind == IN)
			((t_ast_in *)ast)->input = expand_all(((t_ast_in *)ast)->input, shell);
		if (node_string_is_none(ast))
		{
			free_ast(node);
			return (NULL);
		}
		ast = ast->next;
    }
	return (node);
}


