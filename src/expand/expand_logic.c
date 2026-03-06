/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_logic.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 03:55:20 by von               #+#    #+#             */
/*   Updated: 2026/03/06 11:22:28 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/mini_shell.h"

int	isword(char *str, int i, int *flags)
{
	int	addquote;
	int	squote;
	int	dquote;

	dquote = str[i] == '"';
	squote = str[i] == '\'';
	addquote = (2 * dquote) + (squote);
	if (!*flags && (squote || dquote))
	{
		*flags += addquote;
		return (0);
	}
	else if (*flags != 1 && str[i] == '$' && str[i + 1]
		&& (str[i] == '?' || ft_isalpha(str[i + 1]
				|| str[i + 1] == '_')))
		return (1);
	else if ((*flags == 1 && squote) || (*flags == 2 && dquote))
	{
		*flags -= addquote;
		return (0);
	}
	return (0);
}

int	lenkey(char *str)
{
	char	*cpy;

	cpy = str;
	if (*str == '?')
		return (1);
	while (*str && (*str == '_' || ft_isalnum(*str)))
		str++;
	return (str - cpy);
}

char	*resolve_key(char *str, int i, char **env)
{
	char	*mkey;
	char	*res;
	char	*key;
	int		len;

	len = lenkey(&str[i]);
	if (!len)
		return (NULL);
	else
		key = ft_substr(str, i, len, 0);
	mkey = get_env_key(key, env);
	free(key);
	if (!mkey)
		mkey = ft_strdup("", 0);
	res = malloc(sizeof(char) * (ft_strlen(str) + ft_strlen(mkey) + 1));
	if (!res)
		free(mkey);
	if (!res)
		return (NULL);
	ft_strlcat(res, str, i);
	ft_strlcat(res, mkey, ft_strlen(mkey));
	ft_strlcat(res, &str[i + len], ft_strlen(&str[i + len]));
	free(mkey);
	return (res);
}

char	*expand(char *str, int flag, char **env)
{
	char	*cpy;
	int		len;
	int		i;

	i = 0;
	while (str[i])
	{
		if ((!flag && str[i] == '$' && str[i + 1]
				&& (str[i + 1] == '?' || ft_isalpha(str[i + 1])
					|| str[i + 1] == '_')) || isword(str, i, &flag))
		{
			cpy = str;
			str = resolve_key(str, i + 1, env);
			flag = 0;
			len = ft_strlen(str) - ft_strlen(cpy);
			free(cpy);
			if (len < 0)
				len *= -1;
			i += len;
		}
		else
			i++;
	}
	return (str);
}

char	**expand_all(char *string, t_data *shell)
{
	char	*expres;
	char	**split;

	expres = expand(string, 0, shell->env);
	if (!expres)
		return (NULL);
	split = split_expand(expres);
	free(expres);
	if (!split)
		return (NULL);
	return (split);
}
