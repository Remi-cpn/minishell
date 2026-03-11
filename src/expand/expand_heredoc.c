/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tseche <tseche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 15:00:12 by von               #+#    #+#             */
/*   Updated: 2026/03/10 17:45:41 by tseche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_logic.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tseche <tseche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 03:55:20 by von               #+#    #+#             */
/*   Updated: 2026/03/06 18:37:35 by tseche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/mini_shell.h"
#include <stdlib.h>

static void	check_quote(char q, int *flag, char *last_quote)
{
	if (q == *last_quote)
	{
		*last_quote = '\0';
		*flag += -1;
	}
	else if (!*flag && (q == '\'' || q == '"'))
	{
		*last_quote = q;
		*flag += 1;
	}
}

static char	*expand_heredoc(char *str, int flag, t_data *shell)
{
	int			len;
	int			i;
	char		last_quote;

	i = 0;
	last_quote = '\0';
	while (str[i])
	{
		len = 1;
		if (!flag && str[i] == '$' && str[i +1]
			&& str[i + 1] == '?')
			str = question_mark(shell, str, &i);
		else if (!flag && str[i] == '$' && str[i + 1]
			&& (ft_isalpha(str[i + 1]) || str[i + 1] == '_'))
		{
			str = resolve_key(str, i + 1, shell->env, &len);
			flag = 0;
		}
		if (!str)
			return (NULL);
		check_quote(str[i], &flag, &last_quote);
		i += len;
	}
	return (str);
}

char	*expand_all_heredoc(char *string, t_data *shell)
{
	char	*expres;
	char	**split;

	expres = expand_heredoc(string, 0, shell);
	if (!expres)
		return (NULL);
	split = split_expand(expres);
	free(expres);
	if (!split)
		return (NULL);
	expres = dequote(split);
	free(split);
	return (expres);
}
