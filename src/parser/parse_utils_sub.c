/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils_sub.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tseche <tseche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 09:59:24 by rcompain          #+#    #+#             */
/*   Updated: 2026/03/12 16:30:52 by tseche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/mini_shell.h"

static int	find_rpar(t_src_info *txt)
{
	int			depth;
	int			i;

	i = txt-> i;
	depth = 1;
	while (txt->src[i] && depth > 0)
	{
		if (txt->src[i] == '(')
			depth++;
		if (txt->src[i] == ')')
			depth--;
		if (depth > 0)
			i++;
	}
	if (depth != 0)
		return (-1);
	return (i - txt->i);
}

t_ast	*parse_subshell(t_src_info *txt, t_ast_type kind, t_data *shell)
{
	t_ast_subshell	*node;
	int				len;
	char			*inter;
	t_token			token;
	int				s_nbr_cmd;

	token = advance(txt, shell);
	free(token.value);
	len = find_rpar(txt);
	if (len == -1)
		report_parsing_error('(', NULL, shell);
	if (len == -1)
		return (NULL);
	inter = ft_strndup(&txt->src[txt->i], 0, len);
	if (!inter)
		return (NULL);
	node = ft_calloc(1, sizeof(t_ast_subshell));
	token = lexer(txt, shell);
	if (token.kind == RPARENTYPE)
	{
		report_parsing_error(')', NULL, shell);
		node = ft_freenull(node);
	}
	if (node)
	{
		node->kind = kind;
		s_nbr_cmd = shell->nbr_cmd;
		shell->nbr_cmd = 1;
		node->inter = parse(inter, shell, 1);
		node->nbr_cmd = shell->nbr_cmd;
		shell->nbr_cmd = s_nbr_cmd;
	}
	txt->i += len + 1;
	free(inter);
	free(token.value);
	return ((t_ast *)node);
}
