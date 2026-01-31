/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lookup.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tseche <tseche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 17:16:22 by tseche            #+#    #+#             */
/*   Updated: 2026/01/31 16:29:01 by tseche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/mini_shell.h"

void	bind(t_lookup *lookup, t_token_type kind, t_look_handler fn)
{
	lookup[kind].fn = fn;
}

//bind(INFTYPE, &parse_input);
//bind $ \" \' to parse_cmd
void	gen_lookup(t_lookup *lookup)
{
	bind(lookup, PIPETYPE, &parse_pipe);
	bind(lookup, SUPTYPE, &parse_output);
	bind(lookup, DSUPTYPE, &parse_output);
	bind(lookup, DINFTYPE, &parse_heredoc);
	bind(lookup, WORDTYPE, &parse_cmd);
}
