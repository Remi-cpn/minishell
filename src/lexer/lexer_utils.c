/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tseche <tseche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 17:34:09 by tseche            #+#    #+#             */
/*   Updated: 2026/01/27 17:33:00 by tseche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ast.h"
#include "../../libft/libft.h"

bool	expect(char *src, t_token_type type)
{
	return (lexer(src).kind == type);
}

t_token	next(char *src)
{
	static int	i = 0;
	t_token		tok;

	tok = lexer(src[i]);
	i += ft_strlen(tok.value);
	return (tok);
}