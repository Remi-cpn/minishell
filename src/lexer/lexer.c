/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 16:01:12 by tseche            #+#    #+#             */
/*   Updated: 2026/02/04 14:33:31 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ast.h"
#include "../../libft/libft.h"

static t_token	token(char *src, t_token_type kind, int n)
{
	char	*tmp;

	if (n == -1)
		return ((t_token){.kind = UNKNOWN, .value = NULL});
	tmp = ft_strndup(src, 0, n);
	//tmp = ft_substr(src, 0, n, 0);
	if (!tmp)
		return ((t_token){});
	return ((t_token){.value = tmp, .kind = kind});
}

int	word(char *src)
{
	int	i;
	int	quote;

	i = 0;
	quote = 0;
	if (src[i] == '\"')
		quote = 2;
	else if (src[i] == '\'')
		quote = 1;
	if (src[i] == '$')
		i++;
	if (ft_isalnum(src[i]))
	{
		while (ft_isalnum(src[i]) || src[i] == '_')
			i++;
	}
	if (quote == 2 && src[i] == '\"')
		return (++i);
	else if (quote == 2)
		return (-1);
	if (quote == 1 && src[i] == '\'')
		return (++i);
	else if (quote == 1)
		return (-1);
	return (i);
}

t_token	lexer(t_src_info *txt)
{
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
			|| txt->src[txt->i] == '\"'))
		return (token(&txt->src[txt->i], WORDTYPE, word(&txt->src[txt->i])));
	if (txt->i >= txt->len)
		return ((t_token){.kind = eof, .value = NULL});
	return ((t_token){.kind = UNKNOWN, .value = NULL});
}
