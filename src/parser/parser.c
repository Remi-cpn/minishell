/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: von <von@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 15:17:31 by tseche            #+#    #+#             */
/*   Updated: 2026/03/11 22:31:27 by von              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ast.h"
#include "../../include/mini_shell.h"
#include "../../libft/libft.h"
#include <errno.h>
#include <unistd.h>

t_ast	*parse_expr(t_lookup *lookup, t_src_info *txt, t_data *shell)
{
	const t_token	tok = lexer(txt);
	t_look_handler	fn;
	t_ast			*tmp;

	free(tok.value);
	if (tok.kind == UNKNOWN)
		return (NULL);
	if (tok.kind == eof)
	{
		tmp = malloc(sizeof(t_ast));
		if (!tmp)
			return (NULL);
		tmp->kind = END;
		tmp->next = NULL;
		return (tmp);
	}
	fn = lookup[tok.kind].fn;
	if (!fn)
		return (NULL);
	tmp = fn(txt, lookup[tok.kind].type, shell);
	if (!tmp)
		errno = 1;
	else
		tmp->next = NULL;
	return (tmp);
}

t_src_info	*init_parse(char *src, t_lookup *lookup,
	t_ast **next, t_ast ***node)
{
	t_src_info	*txt;

	txt = ft_calloc(sizeof(t_src_info), 1);
	if (!txt)
		return (NULL);
	txt->src = src;
	txt->len = ft_strlen(src);
	gen_lookup(lookup);
	*next = NULL;
	*node = ft_calloc(sizeof(t_list *), 1);
	if (!*node)
		*node = NULL;
	return (txt);
}

t_ast	*next_expr(
	t_lookup *lookup,
	t_src_info *txt,
	t_ast **node,
	t_data	*shell
)
{
	t_ast		*tmp;

	txt->i += skip_whitespace(&txt->src[txt->i]);
	tmp = parse_expr(lookup, txt, shell);
	if (!tmp)
	{
		free(node);
		free(txt);
		return (NULL);
	}
	if ((tmp->kind == OR || tmp->kind == AND || tmp->kind == PIPE)
		&& shell->need_cmd)
	{
		report_parsing_error(txt->src[txt->i - 1], NULL);
		free(tmp);
		return (NULL);
	}
	else if (tmp->kind == OR || tmp->kind == AND || tmp->kind == PIPE)
		shell->need_cmd = 1;
	else
		shell->need_cmd = 0;
	return (tmp);
}

t_ast	**set_flag(
	t_ast **node,
	t_ast *next,
	t_src_info *txt,
	t_data *shell
)
{
	if (!next || !node || !txt)
	{
		shell->error_status = ERR_ALLOC;
		if (node)
			free_ast(node);
		node = ft_freenull(node);
	}
	free(txt);
	return (node);
}

t_ast	**parse(char *src, t_data *shell)
{
	t_ast		**node;
	t_ast		*next;
	t_src_info	*txt;
	t_lookup	lookup[13];

	txt = init_parse(src, lookup, &next, &node);
	shell->need_cmd = 1;
	if (node && txt)
	{
		next = next_expr(lookup, txt, node, shell);
		if (next)
			*node = next;
		while (node && next && next->kind != END)
		{
			if (next->kind == CMD || next->kind == SUBSHELL)
				shell->nbr_cmd++;
			next = next_expr(lookup, txt, node, shell);
			node = check_last(node, next, txt);
			if (!node || !next)
				break ;
			ft_lstadd_back((t_list **)node, (t_list *)next);
		}
	}
	node = set_flag(node, next, txt, shell);
	return (node);
}
