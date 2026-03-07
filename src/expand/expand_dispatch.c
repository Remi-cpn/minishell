/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dispatch.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tseche <tseche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 18:17:34 by tseche            #+#    #+#             */
/*   Updated: 2026/03/06 19:02:31 by tseche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/mini_shell.h"

static char	*rm(int *flag, char *str, int *i)
{
	int	squote;
	int	dquote;
	int	addquote;

	squote = (str[*i] == '\'');
	dquote = (str[*i] == '"');
	addquote = (2 * dquote) + squote;
	if (!*flag && (squote || dquote))
	{
		*flag += addquote;
		ft_memmove(&str[*i], &str[*i + 1], ft_strlen(&str[*i]));
	}
	else if ((*flag == 1 && squote) || (*flag == 2 && dquote))
	{
		*flag -= addquote;
		ft_memmove(&str[*i], &str[*i + 1], ft_strlen(&str[*i]));
	}
	else
		*i += 1;
	if (!str)
		return (NULL);
	return (str);
}

static char	*dequote(char **list)
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

static void	dequote_range(char **new, int start, int end)
{
	char	*pair[2];

	pair[1] = NULL;
	while (start < end)
	{
		pair[0] = new[start];
		new[start] = dequote(pair);
		start++;
	}
}

char	**dispatch_expand(char **args, t_data *shell, char **new, int nbr_files)
{
	int		i;
	int		k;
	int		added;
	char	**tmp;

	i = 0;
	k = 0;
	while (args[i])
	{
		tmp = expand_all(args[i++], shell);
		if (!tmp)
			return (free_array(new), free(args), NULL);
		added = wildcard(new, k, tmp, nbr_files);
		if (added < 0)
			return (free_array(new), free(args), NULL);
		dequote_range(new, k, k + added);
		k += added;
	}
	return (new);
}
