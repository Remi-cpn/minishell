/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tseche <tseche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 16:41:02 by tseche            #+#    #+#             */
/*   Updated: 2026/01/29 00:53:59 by tseche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../../include/ast.h"
#include "../../libft/libft.h"

t_ast	*parse_pipe(t_src_info txt)
{
	t_ast_pipe	*node;

	node = malloc(sizeof(t_ast_pipe));
	if (!node)
		return (NULL);
	advance(txt);
	node->kind = PIPE;
	return ((t_ast *)node);
}

t_ast	*parse_heredoc(t_src_info txt)
{
	t_ast_pipe	*node;

	node = malloc(sizeof(t_ast_heredoc));
	if (!node)
		return (NULL);
	advance(txt);
	node->kind = HEREDOC;
	return ((t_ast *)node);
}

t_ast	*parse_output(t_src_info txt)
{
	t_ast_out	*node;
	t_token		tok;

	node = malloc(sizeof(t_ast_out));
	if (!node)
		return (NULL);
	node->kind = OUT;
	tok = advance(txt);
	node->output = tok.value;
	node->overwrite = true;
	if (tok.kind == DSUPTYPE)
		node->overwrite = false;
	return ((t_ast *)node);
}

//do parse word ($tmp, "tmp", 'tmp', ...)
t_ast	*parse_cmd(t_src_info txt)
{
	t_ast_cmd	*node;

	node = malloc(sizeof(t_ast_cmd));
	if (!node)
		return (NULL);
	node->kind = CMD;
	if (!expect(txt, WORDTYPE))
		//throw error NOT WORDTYPE
	node->name = advance(txt).value;
	if (!node->name)
		return (NULL);
	node->args = NULL;
	while (expect(txt, WORDTYPE))
	{
		node->args = ft_strjoin(node->args, advance(txt).value, 0, 0);
		if (!node->args)
			return (NULL);
	}
	return ((t_ast *)node);
}
