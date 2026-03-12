/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lookup.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tseche <tseche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 17:16:22 by tseche            #+#    #+#             */
/*   Updated: 2026/03/12 17:10:07 by tseche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/mini_shell.h"

void	bind(t_lookup *lookup, t_token_type kind,
			t_look_handler fn, t_ast_type type)
{
	lookup[kind].fn = fn;
	lookup[kind].type = type;
}

//bind(INFTYPE, &parse_input);
//bind $ \" \' to parse_cmd
void	gen_lookup(t_lookup *lookup)
{
	bind(lookup, AMPERTYPE, &parse_ord, AND);
	bind(lookup, VERBARTYPE, &parse_ord, OR);
	bind(lookup, PIPETYPE, &parse_ord, PIPE);
	bind(lookup, DINFTYPE, &parse_heredoc, HEREDOC);
	bind(lookup, SUPTYPE, &parse_output, OUT);
	bind(lookup, DSUPTYPE, &parse_output, OUT);
	bind(lookup, INFTYPE, &parse_input, IN);
	bind(lookup, WORDTYPE, &parse_cmd, CMD);
}
