/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tseche <tseche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 17:34:09 by tseche            #+#    #+#             */
/*   Updated: 2026/02/07 15:56:48 by tseche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/mini_shell.h"

bool	expect(t_src_info *txt, t_token_type type)
{
	t_token	tok;
	bool	res;

	tok = lexer(txt);
	if (tok.kind ==)
		return (false);
	res = tok.kind == type;
	free(tok);
	return (res);
}

t_token	advance(t_src_info *txt)
{
	t_token		tok;

	tok = lexer(txt);
	if (tok.kind == UNKNOWN || tok.kind == eof)
		txt->i += 1;
	else
		txt->i += ft_strlen(tok.value);
	return (tok);
}
