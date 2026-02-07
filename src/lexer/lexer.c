/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tseche <tseche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 16:01:12 by tseche            #+#    #+#             */
/*   Updated: 2026/02/07 15:56:04 by tseche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include "../../include/ast.h"
#include "../../libft/libft.h"
#include "../../include/exit.h"

static t_token	token(char *src, t_token_type kind, int n)
{
	char	*tmp;

	if (n == -1)
		return ((t_token){.kind = UNKNOWN, .value = NULL});
	tmp = ft_strndup(src, 0, n - 1);
	if (!tmp)
		return ((t_token){.kind = ERROR, .value = NULL});
	return ((t_token){.value = tmp, .kind = kind});
}

int	word(char *src)
{
	int	i;
	int	len_quote;

	i = 0;
	while (src[i])
	{
		if (i == 0 && (!ft_isalpha(src[i]) && src[i] != '_' && src[i] != '-'))
			return (-1);
		if (src[i] == '\"' || src[i] == '\'')
		{
			len_quote = len_quoted(&src[i], src[i]);
			if (len_quote == -1)
			{
				print_error(NULL, NULL, 0, "unfinished quotation");
				errno = 1;
				return (-1);
			}
			i += len_quote;
		}
		else if (!ft_iswhitespace(src[i]))
			i++;
		else
			break ;
	}
	return (i);
}

t_token	lexer(t_src_info *txt)
{
	while (ft_iswhitespace(txt->src[txt->i]))
		txt->i++;
	if (txt->i < txt->len && ft_strncmp(&txt->src[txt->i], "<<", 2) == 0)
		return (token(&txt->src[txt->i], DINFTYPE, 2));
	else if (txt->i < txt->len && ft_strncmp(&txt->src[txt->i], ">>", 2) == 0)
		return (token(&txt->src[txt->i], DSUPTYPE, 2));
	else if (txt->i < txt->len && ft_strncmp(&txt->src[txt->i], "&&", 2) == 0)
		return (token(&txt->src[txt->i], AMPERTYPE, 2));
	else if (txt->i < txt->len && ft_strncmp(&txt->src[txt->i], "||", 2) == 0)
		return (token(&txt->src[txt->i], VERBARTYPE, 2));
	else if (txt->i < txt->len && ft_strncmp(&txt->src[txt->i], ">", 1) == 0)
		return (token(&txt->src[txt->i], SUPTYPE, 1));
	else if (txt->i < txt->len && ft_strncmp(&txt->src[txt->i], "<", 1) == 0)
		return (token(&txt->src[txt->i], INFTYPE, 1));
	else if (txt->i < txt->len && ft_strncmp(&txt->src[txt->i], "|", 1) == 0)
		return (token(&txt->src[txt->i], PIPETYPE, 1));
	else if (txt->i < txt->len && (ft_isalnum(txt->src[txt->i])
			|| txt->src[txt->i] == '$' || txt->src[txt->i] == '\''
			|| txt->src[txt->i] == '\"' || txt->src[txt->i] == '-'))
		return (token(&txt->src[txt->i], WORDTYPE, word(&txt->src[txt->i])));
	if (txt->i >= txt->len)
		return ((t_token){.kind = eof, .value = NULL});
	return ((t_token){.kind = UNKNOWN, .value = NULL});
}
