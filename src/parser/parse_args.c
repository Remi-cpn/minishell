/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tseche <tseche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 05:27:48 by tseche            #+#    #+#             */
/*   Updated: 2026/02/11 15:43:41 by von              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/mini_shell.h"

void	free_node(t_ast_cmd *node)
{
	ft_freedb_ptr((void **)node->args);
	free(node->name);
	free(node);
}

t_ast	*parse_args_cmd(t_ast_cmd *node, t_src_info *txt)
{
	int			i;
	t_token		tmp;

	i = 0;
	while (node->args)
	{
		tmp = lexer(txt);
		if (tmp.kind == WORDTYPE)
			node->args[i++] = advance(txt).value;
		else if (tmp.kind != UNKNOWN)
		{
			if (tmp.kind == eof)
				break ;
			free(tmp.value);
			break ;
		}
		else
		{
			free_node(node);
			return (NULL);
		}
		txt->i += skip_whitespace(&txt->src[txt->i]);
		free(tmp.value);
	}
	return ((t_ast *)node);
}

t_ast	**check_last(t_ast **node, t_ast *next, t_src_info *txt)
{
	t_ast	*last;

	if (!node || !next)
		return (NULL);
	last = (t_ast *)ft_lstlast((t_list *)*node);
	if (next->kind == END && (last->kind == PIPE
		|| last->kind == AND || last->kind == OR))
	{
		free(next);
		report_parsing_error(txt->src[txt->i - 1], NULL);
		free_ast(node);
		return (NULL);
	}
	return (node);
}
