/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tseche <tseche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 16:01:12 by tseche            #+#    #+#             */
/*   Updated: 2026/03/10 17:12:58 by tseche           ###   ########.fr       */
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
		return ((t_token){.kind = UNKNOWN, .value = NULL});
	return ((t_token){.value = tmp, .kind = kind});
}

void	report_parsing_error(char c, char *s)
{
	if (c)
		ft_printf("Syntax error near unexpected token `%c\'\n", c);
	else
		ft_printf("Syntax error near unexpected token `%s\'\n",
			s);
	errno = 1;
}

t_token	lexer(t_src_info *txt)
{
	txt->i += skip_whitespace(&txt->src[txt->i]);
	if (txt->i >= txt->len)
		return ((t_token){.kind = eof, .value = NULL});
	else if (ft_strncmp(&txt->src[txt->i], "<<", 2) == 0)
		return (token(&txt->src[txt->i], DINFTYPE, 2));
	else if (ft_strncmp(&txt->src[txt->i], ">>", 2) == 0)
		return (token(&txt->src[txt->i], DSUPTYPE, 2));
	else if (ft_strncmp(&txt->src[txt->i], "&&", 2) == 0)
		return (token(&txt->src[txt->i], AMPERTYPE, 2));
	else if (ft_strncmp(&txt->src[txt->i], "||", 2) == 0)
		return (token(&txt->src[txt->i], VERBARTYPE, 2));
	else if (txt->src[txt->i] == '(')
		return (token(&txt->src[txt->i], LPARENTYPE, 1));
	else if (txt->src[txt->i] == ')')
		return (token(&txt->src[txt->i], RPARENTYPE, 1));
	else if (txt->src[txt->i] == '>')
		return (token(&txt->src[txt->i], SUPTYPE, 1));
	else if (txt->src[txt->i] == '<')
		return (token(&txt->src[txt->i], INFTYPE, 1));
	else if (txt->src[txt->i] == '|')
		return (token(&txt->src[txt->i], PIPETYPE, 1));
	else if (is_start_word(txt->src[txt->i]))
		return (token(&txt->src[txt->i], WORDTYPE,
				len_word(&txt->src[txt->i])));
	return ((t_token){.kind = UNKNOWN, .value = NULL});
}
