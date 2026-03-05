/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: von <von@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 12:48:42 by tseche            #+#    #+#             */
/*   Updated: 2026/03/05 21:12:20 by von              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/mini_shell.h"
#include <stdlib.h>

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

char	*rm(int *flag, char  *str, int *i)
{
	int	squote;
	int	dquote;
	int	addquote;

	squote = (str[*i] == '\'');
	dquote = (str[*i] == '"');
	addquote = (2 * dquote) + squote;
	if (!flag && (squote || dquote))
	{
		*flag += addquote;
		str = ft_strjoin(str, &str[*i + 1], 1, 0);
	}
	else if ((*flag == 1 && squote) || (*flag == 2 && dquote))
	{
		*flag -= addquote;
		str = ft_strjoin(str, &str[*i + 1], 1, 0);
	}
	else
		*i += 1;
	if (!str)
		return (NULL);
	return (str);
}

char	*dequote(char **list)
{
	int		flag;
	char	*res;
	int		i;
	char	*str;

	res = malloc(sizeof(char));
	res[0] = '\0';
	while (*list)
	{
		flag = 0;
		i = 0;
		str = *list;
		while (str[i])
		{
			str = rm(&flag, str, &i);
			if (!str || !str[i])
				break ;
		}
		res = ft_strjoin(res, str, 1, 1);
		if (!res)
			return (NULL);
		list++;
	}
	return (res);
}

//dswmoslewaufIFSr:
// Does some weird modification on string
// like expand, wildcards, and unquoting following IFS rules
char **expansion(char **args, t_data *shell)
{
	char	**tmp;
	char	**wild;
	char	**new;
	int		i;
	
	
	new = ft_calloc(sizeof(char *), (ft_tablen(args) + 1));
	i = 0;
	while (new && args[i])
	{
		tmp = expand_all(args[i], shell);
		if (!tmp)
			free_array(new);
		if (!tmp)
			return (NULL);
		wild = wildcard(tmp);
		free_array(tmp);
		if (!wild)
			free_array(new);
		if (!wild)
			return (NULL);
		new[i] = dequote(wild);
			
		i++;
	}
	free(args);
	return (new);
}
