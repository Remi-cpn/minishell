/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: von <von@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 17:34:09 by tseche            #+#    #+#             */
/*   Updated: 2026/03/12 02:22:24 by von              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/mini_shell.h"

bool	expect(t_src_info *txt, t_token_type type, t_data *shell)
{
	t_token	tok;
	bool	res;

	tok = lexer(txt, shell);
	if (tok.kind == UNKNOWN)
		return (false);
	res = tok.kind == type;
	free(tok.value);
	return (res);
}

t_token	advance(t_src_info *txt, t_data *shell)
{
	t_token		tok;

	tok = lexer(txt, shell);
	if (tok.kind == UNKNOWN || tok.kind == eof)
		txt->i += 1;
	else
		txt->i += ft_strlen(tok.value);
	return (tok);
}
