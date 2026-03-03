/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_logic.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: von <von@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 03:55:20 by von               #+#    #+#             */
/*   Updated: 2026/03/03 01:04:29 by von              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/mini_shell.h"

char	**expand(char *string, char **env, char last_quote, int in)
{
	char	**new;
	char	**ret_exp;
	int		index;
	char	c;
	char	*temp;
	int		lenght;
	int		start;

	index = 0;
	start = 0;
	//div par 2 car bind les " sont present pour ouvrir et ferme
	lenght = (ft_occurence(string, '"') / 2) + ft_occurence(string, '$') + 1;
	new = malloc(sizeof(char *) * (lenght + 1));
	for (int i = 0; i < lenght; i++)
	{
		new[i] = malloc(sizeof(char));
		new[i] = "";
	}
	new[lenght] = NULL;
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
			index += dollar(&string[index], &new, (int[2]){start, index}, env);
			start += 1;
		}
		else if (c == '"')
		{
			if (last_quote == '"' && in)
			{
				free(string);
				return (new);
			}
			last_quote = '"';
			temp = ft_substr(string, index + 1, ft_strchr(&string[index + 1], '"') - &string[index], 0);
			if (!temp)
				return (NULL);
			ret_exp = expand(temp, env, last_quote, 1);
			new = join_dbchar(new, ret_exp, &start, &lenght);
			index += ft_strlen(temp);
		}
		else
		{
			if (c == '\'')
			{
				last_quote = '\'';
				index += cp_raw(&new, string, last_quote, (int [2]){[0] = start, [1] = index});
			}
			else
				index += cp_raw(&new, string, last_quote, (int [2]){[0] = start, [1] = index});
			start += 1;
			last_quote = '"';
		}
	}
	new[lenght] = NULL;
	return (new);
}

char	**list_split(char **list, t_data *shell)
{
	char	**res;
	char	**tmp;
	int		j;
	int		i;
	int		len;

	len = 1;
	for (int i = 0; list[i]; i++)
		len += ft_occurence(list[i], '"') / 2 + ft_occurence(list[i], '$');
	res = malloc(sizeof(char *) * (len + 1));
	if (!list || !res)
		shell->error_status = ERR_ALLOC;
	if (!list || !res)
		return (NULL);
	j = 0;
	while (j < len)
	{
		if (!list[j])
			free_expand(list, len, shell);
		if (!list[j])
			return (NULL);
		tmp = ft_split(list[j], ' ');
		if (!tmp)
			free_expand(list,  len, shell);
		if (!tmp)
			return (NULL);
		i = 0;
		while (tmp[i] && *tmp[i])
			res[j++] = tmp[i++];
	}
	res[j] = NULL;
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
        if ((*s == '"' || *s == '\'') && (*(s+1)))
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
	res = "";
	while (list[i] && *list[i])
    {
        sdequote = dequote_string(list[i]);
        if (!sdequote)
        {
            shell->error_status = ERR_ALLOC;
            free(res);
            return (NULL);
        }
        res = ft_strjoin(res, sdequote, 0, 1);
		if (!res)
		{
			shell->error_status = ERR_ALLOC;
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

	if (!string || !*string)
		return (NULL);
	expres = expand(string, shell->env, '"', 0);
	free(string);
	split = list_split(expres, shell);
	free_array(expres);
	res = NULL;
	if (split)
	{
		res = dequote(split, shell);
		free_array(split);
	}
	return (res);
}
