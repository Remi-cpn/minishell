/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: von <von@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 12:48:42 by tseche            #+#    #+#             */
/*   Updated: 2026/02/24 14:47:19 by von              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/mini_shell.h"

static char	*get_env_key(char *str, char **env, size_t n)
{
	while (*env)
	{
		if (ft_strncmp(str, *env, n) == 0)
			return (*env);
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

char	*expand(char *str, char **env)
{
	char	*res;
	int		n;
	char	*tmp;

	res = "";
	while (*str){
		if (*str == '\"' && get_env_key(str, env, len_quoted(str, '\"')))
			res = ft_strjoin(res, get_env_key(str, env, len_quoted(str, '\"')), 1, 0);
		if (*str == '\"' && get_env_key(str, env, len_quoted(str, '\"')))
			str += len_quoted(str, '\"');
		else
		{
			n = skip_pattern(str, "\"$");
			tmp = ft_strndup(str, 0, n);
			res = ft_strjoin(res, tmp, 1, 1);
			str += n;
		}
	}
	return (res);
}

void    dispatch_expand(t_ast **node, char **env)
{
	t_ast	*ast;

	ast = *node;
	while (ast->kind != END)
	{
		if (ast->kind == CMD)
		{
			((t_ast_cmd *)ast)->name = expand(((t_ast_cmd *)ast)->name, env);
			while (*((t_ast_cmd *)ast)->args)
			{
				*((t_ast_cmd *)ast)->args = expand(*((t_ast_cmd *)ast)->args, env);
				((t_ast_cmd *)ast)->args++;
			}
		}
		else if (ast->kind == HEREDOC)
			((t_ast_heredoc *)ast)->del = expand(((t_ast_heredoc *)ast)->del, env);
		else if (ast->kind == OUT)
			((t_ast_out *)ast)->output = expand(((t_ast_out *)ast)->output, env);
		else if (ast->kind == IN)
			((t_ast_in *)ast)->input = expand(((t_ast_in *)ast)->input, env);
		ast = ast->next;
    }
}


