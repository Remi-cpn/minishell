/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lookup.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tseche <tseche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 17:16:22 by tseche            #+#    #+#             */
/*   Updated: 2026/01/28 17:25:02 by tseche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ast.h"

void	bind(t_token_type kind, t_look_handler fn)
{
	lookup[kind].fn = fn;
}

void	gen_lookup(void)
{
	bind(PIPETYPE, &parse_pipe);
	
	bind(SUPTYPE, &parse_output);
	bind(DSUPTYPE, &parse_output);

	bind(INFTYPE, &parse_input);

	bind(DINFTYPE, &parse_heredoc);

	bind(WORDTYPE, &parse_cmd);
}