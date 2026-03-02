/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tseche <tseche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 03:52:35 by von               #+#    #+#             */
/*   Updated: 2026/03/02 18:39:24 by tseche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/mini_shell.h"

int	node_string_is_none(t_ast *ast)
{
    int i;
	if (ast->kind == CMD)
	{
		if (!((t_ast_cmd *)ast)->name)
			return (1);
        i = 0;
		while (*((t_ast_cmd *)ast)->args && !((t_ast_cmd *)ast)->args[i++])
			return (1);
	}
	//enlever les quote plutot que expand;
	else if (ast->kind == HEREDOC && ! ((t_ast_heredoc *)ast)->del)
		return (1);
	else if (ast->kind == OUT && !((t_ast_out *)ast)->output)
		return (1);
	else if (ast->kind == IN && !((t_ast_in *)ast)->input)
		return (1);
	return (0);
}

void	free_expand(char **s, int len, t_data *shell)
{
	int	i;

	i = 0;
	shell->error_status = ERR_ALLOC;
	while (i < len)
		free(s[i++]);
}

int	cp_raw(char ***new, char *string, char find, int *thing)
{
	char	*next;
	char	*tmp;
    int     len;

	if (find == '\'')
		next = ft_strchr(&string[1], find);
	else
		next = ft_strchr(string, find);
	if (!next)
	{

		if (find == '\'')
			tmp = ft_substr(string, 0, 1, 0);
		else
			tmp = ft_substr(string, 0, ft_strlen(string), 0);
        len = ft_strlen(tmp);
		(*new)[thing[0]] = ft_strjoin((*new)[thing[0]], tmp, 0, 1);
        return (len);
	}
	else
	{
		tmp = ft_substr(string, 0, next - string, 0);
        if (!(*new)[thing[0]])
            (*new)[thing[0]] = tmp;
        else
		    (*new)[thing[0]] = ft_strjoin((*new)[thing[0]], tmp, 1, 1);
		return (next - string);
	}
}

int	dollar(char *string, char ***new, int *thing, char **env)
{
	int		len;
	char	*tmp;
	char	*key;

	len = 0;
	while (string[len] && !ft_isoneof(string[len], " \"\'"))
		len++;
	if (len == 0)
		tmp = NULL;
	else
	 	tmp = ft_substr(string, 0, len, 0);
	if (!tmp)
	{
		(*new)[thing[0]] = ft_strjoin((*new)[thing[0]], "$", 0, 1);
        return (0);
	}
	else
	{
		key = get_env_key(tmp, env);
		(*new)[thing[0]] = ft_strjoin((*new[thing[0]]), key, 0, 0); 
		free(tmp);
        return (len);
	}
}