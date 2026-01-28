/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_expr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tseche <tseche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 16:41:02 by tseche            #+#    #+#             */
/*   Updated: 2026/01/28 17:15:10 by tseche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ast.h"

t_ast	*parse_expr(char *src)
{
	const t_token			tok = next(src);
	const t_look_handler	fn = lookup[tok.kind].fn;
	t_ast					*tmp;
	
	if (!fn)
		//THROW ERROR
	tmp = fn(src);
	return (tmp);
}