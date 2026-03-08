/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: von <von@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 15:00:12 by von               #+#    #+#             */
/*   Updated: 2026/03/08 16:06:19 by von              ###   ########.fr       */
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

static char	*expand_heredoc(char *str, int flag, t_data *shell)
{
	char	*cpy;
	int		len;
	int		i;
	int		last_quote;

	i = 0;
	last_quote = '\0';
	while (str[i])
	{
		if (!flag && str[i] == '$' && str[i + 1]
				&& (ft_isalpha(str[i + 1]) || str[i + 1] == '_'))
        {
			cpy = str;
			str = resolve_key(str, i + 1, shell->env);
			flag = 0;
			if (!str)
			{
				str = cpy;
				i += lenkey(&str[i]);
				continue ;
			}
			len = ft_strlen(str) - ft_strlen(cpy);
			free(cpy);
			if (len < 0)
				len *= -1;
			i += len;
		}
		else if (!flag && str[i] == '$' && str[i +1]
			&& str[i + 1] == '?')
			str = question_mark(shell, str, &i);
		else
		{
			if (str[i] == last_quote)
			{
				last_quote = '\0';
				flag--;
			}
			else if (!flag && (str[i] == '"' || str[i] == '\''))
			{
				last_quote = str[i];
				flag++;
			}	
			i++;
		}
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
