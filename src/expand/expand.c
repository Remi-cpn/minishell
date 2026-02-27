/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: von <von@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 12:48:42 by tseche            #+#    #+#             */
/*   Updated: 2026/02/27 19:40:11 by von              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/mini_shell.h"
#include <stdlib.h>

static char	*get_env_key(char *str, char **env)
{
	while (*env)
	{
		if (ft_strncmp(str, *env, ft_strlen(*env)) == 0)
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

char	**join_dbchar(char **string, char **add, int *start, int *lenght)
{
	int		i;
	char	**tmp;

	i = 0;
	while (add[i])
	{
		if (string[*start])
			free(string[*start]);
		else if (i > *lenght)
		{
			tmp = string;
			string = ft_realloc(string, *lenght, *lenght * 2, sizeof(char *));
			free_array(tmp);
			if (!string)
				return (NULL);
			*lenght *= 2;
		}
		string[*start++] = add[i++];
	}
	return (string);
}

void	dollar(char *string, char ***new, int *thing, char **env)
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
		(*new)[thing[0]] = ft_strjoin((*new)[thing[0]], "$\0", 0, 1);
	}
	else
	{
		key = get_env_key(tmp, env);
		(*new)[thing[0]] = ft_strjoin((*new[thing[0]]), key, 0, 0); 
		thing[1] += len;
	}
	thing[0]++;
}

void	cp_raw(char ***new, char *string, char find, int *thing)
{
	char	*next;
	char	*tmp;

	next = ft_strchr(string, find);
	if (!next)
	{
		tmp = ft_substr(string, 0, ft_strlen(string), 0);
		(*new)[thing[0]] = ft_strjoin((*new)[thing[0]], tmp, 1, 1);
	}
	else
	{
		tmp = ft_substr(string, 0, next - string, 0);
		(*new)[thing[0]] = ft_strjoin((*new)[thing[0]], tmp, 1, 1);
		thing[1] += next - string;
	}
}

char	**expand(char *string, int quoted, char **env, int *start)
{
	char	**new;
	int		index;
	char	c;
	char	*temp;
	int		lenght;

	index = 0;
	start = 0;
	lenght = ft_occurence(string, '"') + 1;
	new = malloc(sizeof(char *) * lenght + 1);
	if (!new)
		return (NULL);
	while (1)
	{
		c = string[index];
		if (c == 0)
			break ;
		else if (c == '$')
		{
			index++;
			dollar(&string[index], &new, (int[2]){*start, index}, env);
		}
		else if (c == '\'')
			cp_raw(&new, string, '\'', (int [2]){[0] = *start, [1] = index});
		else if (c == '"')
		{
			if (quoted)
				return (new);
			temp = ft_substr(string, index + 1, ft_strchr(&string[index + 1], '"') - &string[index], 0);
			if (!temp)
				return (NULL);
			new = join_dbchar(new, expand(temp, 1, env, start), &start, &lenght);
			index += ft_strlen(temp);
		}
		else
			cp_raw(&new, string, '"', (int [2]){[0] = *start, [1] = index});
	}
	new[*start] = NULL;
	return (new);
}

void	free_expand(char **s, int len, t_data *shell)
{
	int	i;

	i = 0;
	shell->exit_status = ERR_ALLOC;
	while (i < len)
		free(s[i++]);
}
char	**list_split(char **list, t_data *shell, int *len)
{
	char	**res;
	char	**tmp;
	static int		j = 0;
	int		i;

	res = malloc(sizeof(char *) * *len);
	if (!list || !res)
		shell->exit_status = ERR_ALLOC;
	if (!list || !res)
		return (NULL);
	while (j < *len)
	{
		if (!list[j])
			free_expand(list, *len, shell);
		if (!list[j])
			return (NULL);
		tmp = ft_split(list[j], ' ');
		if (!tmp)
			free_expand(list,  *len, shell);
		if (!tmp)
			return (NULL);
		i = 0;
		while (tmp[i])
			res[j++] = tmp[i++];
	}
	return (res);
}

char *dequote_string(char *s)
{
	char 	*res;
	int		i;
    //possibly allocate more than needed
    res = malloc(sizeof(char) * (strlen(s) + 1));
    if (!res)
		return (NULL);
	i = 0;
    while (*s)
    {
        if (*s == '"' || *s == '\'')
        {
            s++;
            if (!*s)
                break ;
            continue ;
        }
        res[i++] = *s++;
    }
	res[i] = '\0';
    return (res);
}

char *dequote(char **list, t_data *shell)
{
    char	*res;
    char	*sdequote;
	int		i;

	i = 0;
	while (list[i])
    {
        sdequote = dequote_string(list[i]);
        if (!sdequote)
        {
            shell->exit_status = ERR_ALLOC;
            free(res);
            return (NULL);
        }
        res = ft_strjoin(res, sdequote, 1, 1);
		if (!res)
		{
			free(sdequote);
			shell->exit_status = ERR_ALLOC;
			return (NULL);
		}
		i++;
	}
    return (res);
}

char	*expand_all(char *string, t_data *shell)
{
	char	**expres;
	char	**split;
	char	*res;
	int		len;

	len = 0;
	expres = expand(string, 1, shell->env, &len);
	split = list_split(expres, shell, &len);
	free_array(expres);
	res = NULL;
	if (split)
	{
		res = dequote(split, shell);
		free_array(split);
	}
	return (res);
}


void    dispatch_expand(t_ast **node, t_data *shell)
{
	t_ast	*ast;

	ast = *node;
	while (ast->kind != END)
	{
		//check tout les retour de expand
		if (ast->kind == CMD)
		{
			((t_ast_cmd *)ast)->name = expand_all(((t_ast_cmd *)ast)->name, shell);
			while (*((t_ast_cmd *)ast)->args)
			{
				*((t_ast_cmd *)ast)->args = expand_all(*((t_ast_cmd *)ast)->args, shell);
				((t_ast_cmd *)ast)->args++;
			}
		}
		//enlever les quote plutot que expand;
		else if (ast->kind == HEREDOC)
			((t_ast_heredoc *)ast)->del = expand_all(((t_ast_heredoc *)ast)->del, shell);
		else if (ast->kind == OUT)
			((t_ast_out *)ast)->output = expand_all(((t_ast_out *)ast)->output, shell);
		else if (ast->kind == IN)
			((t_ast_in *)ast)->input = expand_all(((t_ast_in *)ast)->input, shell);
		ast = ast->next;
    }
}


