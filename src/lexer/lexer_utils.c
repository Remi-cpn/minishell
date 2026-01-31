/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tseche <tseche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 17:34:09 by tseche            #+#    #+#             */
/*   Updated: 2026/01/31 15:36:50 by tseche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/mini_shell.h"

bool	expect(t_src_info txt, t_token_type type)
{
	return (lexer(txt).kind == type);
}

t_token	advance(t_src_info txt)
{
	t_token		tok;

	tok = lexer(txt);
	if (tok.kind == UNKNOWN)
		txt.i += 1;
	else
		txt.i += ft_strlen(tok.value);
	return (tok);
}
