/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tseche <tseche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 16:41:02 by tseche            #+#    #+#             */
/*   Updated: 2026/02/09 04:23:55 by tseche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <errno.h>
#include "../../include/mini_shell.h"
#include "../../libft/libft.h"

t_ast	*parse_ord(t_src_info *txt, t_ast_type kind)
{
	t_ast_pipe	*node;
	t_token		tok;

	tok = advance(txt);
	free(tok.value);
	node = malloc(sizeof(t_ast_pipe));
	if (!node)
		return (NULL);
	node->kind = kind;
	return ((t_ast *)node);
}

t_ast	*parse_heredoc(t_src_info *txt, t_ast_type kind)
{
	t_ast_heredoc	*node;
	t_token			tok;

	tok = advance(txt);
	free(tok.value);
	node = malloc(sizeof(t_ast_heredoc));
	if (!node)
		return (NULL);
	node->kind = kind;
	tok = advance(txt);
	if (tok.kind != WORDTYPE)
	{
		
		ft_printf("Syntax error near unexpected token `%s\'\n", tok.value);
		errno = 1;
		return (NULL);
	}
	node->del = tok.value;
	return ((t_ast *)node);
}

t_ast	*parse_output(t_src_info *txt, t_ast_type kind)
{
	t_ast_out	*node;
	t_token		tok;

	tok = advance(txt);
	free(tok.value);
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
	t_token		tmp;

	node = ft_calloc(1, sizeof(t_ast_cmd));
	if (!node)
		return (NULL);
	node->kind = kind;
	if (!expect(txt, WORDTYPE))
	{
		free(node);
		return (NULL);
	}
	node->name = advance(txt).value;
	if (!node->name)
	{
		free(node);
		return (NULL);
	}
	i = ft_count_word(&txt->src[txt->i], ' ') + 1;
	node->args = ft_calloc(sizeof(t_ast *), i);
	i = 0;
	while (node->args)
	{
		tmp = lexer(txt);
		if (tmp.kind == WORDTYPE)
			node->args[i] = advance(txt).value;
		else if (tmp.kind != WORDTYPE && tmp.kind != UNKNOWN)
		{
			if (tmp.kind == eof)
				break ;
			free(tmp.value);
			break ;
		}
		else//tmp.kind == UNKNOWN
		{
			ft_freedb_ptr((void **)node->args);
			free(node->name);
			free(node);
			return (NULL);
		}
		while (ft_iswhitespace(txt->src[txt->i]))
			txt->i++;
		free(tmp.value);
	}
	return ((t_ast *)node);
}
