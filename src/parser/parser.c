/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tseche <tseche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 15:17:31 by tseche            #+#    #+#             */
/*   Updated: 2026/02/09 02:32:58 by tseche           ###   ########.fr       */
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
	tmp->next = NULL;
	return (tmp);
}

t_ast	**parse(char *src, t_data *shell)
{
	t_ast		**node;
	t_ast		*tmp;
	t_src_info	*txt;
	t_lookup	lookup[13];
	bool		need_cmd;

	gen_lookup(lookup);
	txt = ft_calloc(sizeof(t_src_info), 1);
	if (!txt)
		return (NULL);
	txt->src = src;
	txt->len = ft_strlen(src);
	need_cmd = 1;
	node = ft_calloc(sizeof(t_list *), 1);
	tmp = parse_expr(lookup, txt);
	if (need_cmd && ((tmp->kind == AND || tmp->kind == OR)))
	{
		ft_printf("Syntax error near unexpected token `%c\'\n", txt->src[txt->i]);
		errno = 1;
	}
	if (tmp && node)
	{
		*node = tmp;
		if (tmp->kind == CMD)
			shell->nbr_cmd++;
		while (tmp->kind != END)
		{
			while (ft_iswhitespace(txt->src[txt->i]))
				txt->i++;
			tmp = parse_expr(lookup, txt);
			if ((tmp->kind == OR || tmp->kind == AND) && need_cmd)
					need_cmd = 0;
			else if (tmp->kind == OR || tmp->kind == AND)
			{
				ft_printf("Syntax error near unexpected token `%c\'\n", txt->src[txt->i]);
				errno = 1;
			}
			else if (tmp->kind == CMD)
				need_cmd = 0;
			if (!tmp)
				break ;
			ft_lstadd_back((t_list **)node, (t_list *)tmp);
			if (!node)
				break ;
			if (tmp->kind == CMD)
				shell->nbr_cmd++;
		}
	}
	if (!tmp || !node)
		shell->exit_status = ERR_ALLOC;
	free(txt);
	return (node);
}
