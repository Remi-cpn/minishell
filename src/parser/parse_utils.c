/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tseche <tseche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 16:41:02 by tseche            #+#    #+#             */
/*   Updated: 2026/02/01 18:18:14 by tseche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ast.h"
#include "../../libft/libft.h"
#include <stdlib.h>

t_ast	*parse_pipe(t_src_info *txt)
{
	t_ast_pipe	*node;
	t_token		tok;

	advance(txt);
	node = malloc(sizeof(t_ast_pipe));
	if (!node)
		return (NULL);
	tok = advance(txt);
	if (tok.kind == UNKNOWN)
		return (NULL);
	node->kind = PIPE;
	return ((t_ast *)node);
}

t_ast	*parse_heredoc(t_src_info *txt)
{
	t_ast_pipe	*node;
	t_token		tok;

	advance(txt);
	node = malloc(sizeof(t_ast_heredoc));
	if (!node)
		return (NULL);
	tok = advance(txt);
	if (tok.kind == UNKNOWN)
		return (NULL);
	node->kind = HEREDOC;
	return ((t_ast *)node);
}

t_ast	*parse_output(t_src_info *txt)
{
	t_ast_out	*node;
	t_token		tok;

	advance(txt);
	node = malloc(sizeof(t_ast_out));
	if (!node)
		return (NULL);
	node->kind = OUT;
	tok = advance(txt);
	if (tok.kind == UNKNOWN)
		return (NULL);
	node->output = tok.value;
	node->overwrite = true;
	if (tok.kind == DSUPTYPE)
		node->overwrite = false;
	return ((t_ast *)node);
}

// do parse word ($tmp, "tmp", 'tmp', ...)
t_ast	*parse_cmd(t_src_info *txt)
{
	t_ast_cmd	*node;
	int			i;

	node = malloc(sizeof(t_ast_cmd));
	if (!node)
		return (NULL);
	node->kind = CMD;
	if (!expect(txt, WORDTYPE))
		return (NULL);
	node->name = advance(txt).value;
	if (!node->name)
		return (NULL);
	i = ft_count_word(&txt->src[txt->i], ' ') + 1;
	node->args = ft_calloc(sizeof(t_ast *), i);
	i = 0;
	while (node->args && expect(txt, WORDTYPE))
	{
		node->args[i] = advance(txt).value;
		while ((txt->src[txt->i] >= '\a' && txt->src[txt->i] <= '\r')
			|| txt->src[txt->i] == ' ')
			txt->i++;
		if (!node->args[i++])
			return (NULL);
	}
	return ((t_ast *)node);
}
