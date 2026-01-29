/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tseche <tseche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 17:34:09 by tseche            #+#    #+#             */
/*   Updated: 2026/01/28 23:53:36 by tseche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ast.h"
#include "../../libft/libft.h"

bool	expect(t_src_info txt, t_token_type type)
{
	return (lexer(txt).kind == type);
}

t_token	advance(t_src_info txt)
{
	t_token		tok;

	tok = lexer(txt);
	txt.i += ft_strlen(tok.value);
	return (tok);
}
