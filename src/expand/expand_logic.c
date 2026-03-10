/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_logic.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tseche <tseche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 03:55:20 by von               #+#    #+#             */
/*   Updated: 2026/03/10 17:46:59 by tseche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/mini_shell.h"

int	isword(char *str, int i, int *flags)
{
	int	squote;
	int	dquote;

	dquote = str[i] == '"';
	squote = str[i] == '\'';
	if (!*flags && (squote || dquote))
	{
		*flags += (2 * dquote) + (squote);
		return (0);
	}
	else if (*flags != 1 && str[i] == '$' && str[i + 1]
		&& (str[i + 1] == '?' || ft_isalpha(str[i + 1])
			|| str[i + 1] == '_'))
		return (1);
	else if ((*flags == 1 && squote) || (*flags == 2 && dquote))
	{
		*flags -= (2 * dquote) + (squote);
		return (0);
	}
	return (0);
}

int	lenkey(char *str)
{
	char	*cpy;

	cpy = str;
	if (*str == '?' || *str == '*')
		return (1);
	while (*str && (*str == '_' || ft_isalnum(*str)))
		str++;
	return (str - cpy);
}

char	*resolve_key(char *str, int i, char **env, int *add_len)
{
	char	*mkey;
	char	*res;
	char	*key;
	int		len;
	int		len_mkey;

	len = lenkey(&str[i]);
	*add_len = len;
	key = ft_substr(str, i, len, 0);
	mkey = get_env_key(key, env);
	free(key);
	if (!mkey)
		mkey = "";
	len_mkey = ft_strlen(mkey);
	res = ft_calloc((ft_strlen(str) + len_mkey + 1), sizeof(char));
	if (!res)
		return (NULL);
	ft_strlcat(res, str, i);
	ft_strlcat(res, mkey, len_mkey + i);
	ft_strlcat(res, &str[i + len], ft_strlen(&str[i + len]) + i
		+ len_mkey);
	return (res);
}

char	*expand(char *str, int flag, t_data *shell)
{
	int		len;
	int		i;

	i = 0;
	while (str[i])
	{
		len = 1;
		if (!flag && str[i] == '$' && str[i +1]
			&& str[i + 1] == '?')
			str = question_mark(shell, str, &i);
		else if ((!flag && str[i] == '$' && str[i + 1]
				&& (ft_isalpha(str[i + 1]) || str[i + 1] == '_'
					|| str[i + 1] == '*')) || isword(str, i, &flag))
		{
			str = resolve_key(str, i + 1, shell->env, &len);
			flag = 0;
		}
		if (!str)
			return (NULL);
		i += len;
	}
	return (str);
}

char	**expand_all(char *string, t_data *shell)
{
	char	*expres;
	char	**split;

	expres = expand(string, 0, shell);
	if (!expres)
		return (NULL);
	split = split_expand(expres);
	free(expres);
	if (!split)
		return (NULL);
	return (split);
}
