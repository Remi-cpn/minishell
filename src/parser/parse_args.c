/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: von <von@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 05:27:48 by tseche            #+#    #+#             */
/*   Updated: 2026/03/12 02:24:10 by von              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/mini_shell.h"

void	free_node(t_ast_cmd *node)
{
	ft_freedb_ptr((void **)node->args);
	free(node->name);
	free(node);
}

t_ast	*parse_args_cmd(t_ast_cmd *node, t_src_info *txt, t_data *shell)
{
	int			i;
	t_token		tmp;

	i = 0;
	while (node->args)
	{
		tmp = lexer(txt, shell);
		if (tmp.kind == WORDTYPE)
			node->args[i++] = advance(txt, shell).value;
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
		free(tmp.value);
	}
	return ((t_ast *)node);
}

t_ast	**check_last(t_ast **node, t_ast *next, t_src_info *txt, t_data *shell)
{
	t_ast	*last;

	if (!node || !next)
		return (NULL);
	last = (t_ast *)ft_lstlast((t_list *)*node);
	if (next->kind == END && (last->kind == PIPE
			|| last->kind == AND || last->kind == OR))
	{
		free(next);
		report_parsing_error(txt->src[txt->i - 1], NULL, shell);
		free_ast(node);
		return (NULL);
	}
	return (node);
}
