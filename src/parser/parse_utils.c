/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tseche <tseche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 16:41:02 by tseche            #+#    #+#             */
/*   Updated: 2026/02/06 11:33:07 by tseche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/mini_shell.h"
#include "../../libft/libft.h"
#include <stdlib.h>

t_ast	*parse_ord(t_src_info *txt, t_ast_type kind)
{
	t_ast_pipe	*node;

	advance(txt);
	node = malloc(sizeof(t_ast_pipe));
	if (!node)
		return (NULL);
	node->kind = kind;
	return ((t_ast *)node);
}

t_ast	*parse_output(t_src_info *txt, t_ast_type kind)
{
	t_ast_out	*node;
	t_token		tok;

	advance(txt);
	node = malloc(sizeof(t_ast_out));
	if (!node)
		return (NULL);
	node->kind = kind;
	if (!expect(txt, WORDTYPE))
		return (NULL);
	tok = advance(txt);
	if (tok.kind == UNKNOWN)
		return (NULL);
	node->output = tok.value;
	node->overwrite = true;
	if (tok.kind == DSUPTYPE)
		node->overwrite = false;
	return ((t_ast *)node);
}

t_ast	*parse_input(t_src_info *txt, t_ast_type kind)
{
	t_ast_in	*node;
	t_token		tok;

	advance(txt);
	node = malloc(sizeof(t_ast_in));
	if (!node)
		return (NULL);
	node->kind = kind;
	tok = advance(txt);
	if (tok.kind == UNKNOWN)
		return (NULL);
	node->input = tok.value;
	return ((t_ast *)node);
}

t_ast	*parse_cmd(t_src_info *txt, t_ast_type kind)
{
	t_ast_cmd	*node;
	int			i;

	node = ft_calloc(1, sizeof(t_ast_cmd));
	if (!node)
		return (NULL);
	node->kind = kind;
	if (!expect(txt, WORDTYPE))
		return (NULL);
	node->name = advance(txt).value;
	if (!node->name)
		return (NULL);
	i = ft_count_word(&txt->src[txt->i], ' ') + 1;
	node->args = ft_calloc(sizeof(t_ast *), i);
	i = 0;
	while (node->args)
	{
		if (lexer(txt).kind != UNKNOWN && lexer(txt).kind != eof)
			node->args[i] = advance(txt).value;
		else if (lexer(txt).kind == eof)
			break ;
		else
			return (NULL);
		while (ft_iswhitespace(txt->src[txt->i]))
			txt->i++;
	}
	return ((t_ast *)node);
}
