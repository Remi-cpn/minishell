/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tseche <tseche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 12:48:42 by tseche            #+#    #+#             */
/*   Updated: 2026/03/04 11:32:15 by tseche           ###   ########.fr       */
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
//it don't actually rm the char but overwrite by his following and so on
char	*rm_char(char *str, int pos)
{
	char	cpy;

	cpy = str;
	str += pos + 1;
	while (*str)
		*str = *str + 1;
	return (cpy); 
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
		str = rm_char(str, *i);
	}
	else if ((flag == 1 && squote) || flag == 2 && dquote)
	{
		flag -= addquote;
		str = rm_char(str, *i);
	}
	else
		*i++;
	return (str);
}

char	*dequote(char **list)
{
	int		flag;
	char	*cpy;

	while (*list)
	{
		flag = 0;
		cpy = *list;
		while (**list)
		{
			*list = rm(&flag, *list, &**list - cpy);
			if (*list)
				break ;
		}
		list++;
	}
}

//dswmoslewaufIFSr:
// Does some weird modification on string
// like expand, wildcards, and unquoting following IFS rules
char	*dswmoslewaufIFSr(char *str, t_data *shell)
{
	char	**res;

	res = expand_all(str, shell);
	res = dequote(res);
}
