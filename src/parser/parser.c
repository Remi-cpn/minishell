/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tseche <tseche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 15:17:31 by tseche            #+#    #+#             */
/*   Updated: 2026/02/09 06:20:02 by tseche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ast.h"
#include "../../include/mini_shell.h"
#include "../../libft/libft.h"
#include <errno.h>
#include <unistd.h>

t_ast	*parse_expr(t_lookup *lookup, t_src_info *txt)
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
	tmp = fn(txt, lookup[tok.kind].type);
	if (!tmp)
		errno = 1;
	else
		tmp->next = NULL;
	return (tmp);
}

t_src_info	*init_parse(char *src, t_lookup *lookup)
{
	t_src_info	*txt;

	txt = ft_calloc(sizeof(t_src_info), 1);
	if (!txt)
		return (NULL);
	txt->src = src;
	txt->len = ft_strlen(src);
	gen_lookup(lookup);
	return (txt);
}

t_ast	*next_expr(
	t_lookup *lookup,
	t_src_info *txt,
	t_ast **node
)
{
	static int	need_cmd = 1;
	t_ast		*tmp;

	txt->i += skip_whitespace(&txt->src[txt->i]);
	tmp = parse_expr(lookup, txt);
	if (!tmp)
	{
		free(node);
		free(txt);
		return (NULL);
	}
	if ((tmp->kind == OR || tmp->kind == AND || tmp->kind == PIPE) && need_cmd)
		need_cmd = 0;
	else if (tmp->kind == OR || tmp->kind == AND || tmp->kind == PIPE)
	{
		report_parsing_error(txt->src[txt->i - 1], NULL);
		ft_freedb_ptr((void **)node);
		free(txt);
		free(tmp);
		return (NULL);
	}
	else if (tmp->kind == CMD)
		need_cmd = 0;
	return (tmp);
}

void	set_flag(
	t_ast **node,
	t_ast *next,
	t_src_info *txt,
	t_data *shell
)
{
	if (!next || !node || !txt)
		shell->exit_status = ERR_ALLOC;
	free(txt);
}

t_ast	**parse(char *src, t_data *shell)
{
	t_ast		**node;
	t_ast		*next;
	t_src_info	*txt;
	t_lookup	lookup[13];

	txt = init_parse(src, lookup);
	node = ft_calloc(sizeof(t_list *), 1);
	if (node && txt)
	{
		next = next_expr(lookup, txt, node);
		if (!next)
			return (NULL);
		*node = next;
		while (node && next && next->kind != END)
		{
			if (next->kind == CMD)
				shell->nbr_cmd++;
			next = next_expr(lookup, txt, node);
			if (!node || !next)
				break ;
			ft_lstadd_back((t_list **)node, (t_list *)next);
		}
	}
	return (node);
}
