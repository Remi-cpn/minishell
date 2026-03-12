/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: von <von@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 16:41:02 by tseche            #+#    #+#             */
/*   Updated: 2026/03/12 00:08:37 by von              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../../include/mini_shell.h"
#include "../../libft/libft.h"

t_ast	*parse_ord(t_src_info *txt, t_ast_type kind, t_data *shell)
{
	t_ast_pipe	*node;
	t_token		tok;

	(void)shell;
	tok = advance(txt);
	free(tok.value);
	node = malloc(sizeof(t_ast_pipe));
	if (!node)
		return (NULL);
	node->kind = kind;
	return ((t_ast *)node);
}

t_ast	*parse_heredoc(t_src_info *txt, t_ast_type kind, t_data *shell)
{
	t_ast_heredoc	*node;
	t_token			tok;

	(void)shell;
	tok = advance(txt);
	free(tok.value);
	node = malloc(sizeof(t_ast_heredoc));
	if (!node)
		return (NULL);
	node->kind = kind;
	tok = advance(txt);
	if (tok.kind == UNKNOWN || tok.kind == eof)
	{
		report_parsing_error(0, tok.value);
		free(tok.value);
		free(node);
		return (NULL);
	}
	node->del = tok.value;
	return ((t_ast *)node);
}

t_ast	*parse_output(t_src_info *txt, t_ast_type kind, t_data *shell)
{
	t_ast_out	*node;
	t_token		tok;

	(void)shell;
	tok = advance(txt);
	free(tok.value);
	node = malloc(sizeof(t_ast_out));
	if (!node)
		return (NULL);
	node->kind = kind;
	node->overwrite = tok.kind == SUPTYPE;
	tok = advance(txt);
	if (tok.kind == UNKNOWN || tok.kind == eof)
	{
		report_parsing_error(0, tok.value);
		free(node);
		free(tok.value);
		return (NULL);
	}
	node->output = tok.value;
	return ((t_ast *)node);
}

t_ast	*parse_input(t_src_info *txt, t_ast_type kind, t_data *shell)
{
	t_ast_in	*node;
	t_token		tok;

	(void)shell;
	tok = advance(txt);
	free(tok.value);
	node = malloc(sizeof(t_ast_in));
	if (!node)
		return (NULL);
	node->kind = kind;
	tok = advance(txt);
	if (tok.kind == UNKNOWN || tok.kind == eof)
	{
		report_parsing_error(0, tok.value);
		free(tok.value);
		free(node);
		return (NULL);
	}
	node->input = tok.value;
	return ((t_ast *)node);
}

t_ast	*parse_cmd(t_src_info *txt, t_ast_type kind, t_data *shell)
{
	t_ast_cmd	*node;
	int			i;

	(void)shell;
	node = ft_calloc(1, sizeof(t_ast_cmd));
	if (!node)
		return (NULL);
	node->kind = kind;
	node->name = advance(txt).value;
	if (!node->name)
		free(node);
	if (!node->name)
		return (NULL);
	i = ft_count_word(&txt->src[txt->i], ' ');
	node->args = ft_calloc(sizeof(t_ast *), (i + 1));
	if (!node->args)
	{
		free(node->name);
		free(node);
		return (NULL);
	}
	node = (t_ast_cmd *)parse_args_cmd(node, txt);
	return ((t_ast *)node);
}
