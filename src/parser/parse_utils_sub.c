/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils_sub.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 09:59:24 by rcompain          #+#    #+#             */
/*   Updated: 2026/03/09 11:12:40 by rcompain         ###   ########.fr       */
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
	return (i - txt->i);
}

t_ast	*parse_subshell(t_src_info *txt, t_ast_type kind, t_data *shell)
{
	t_ast_subshell	*node;
	int				len;
	int				s_nbr_cmd;
	char			*inter;

	(void)kind;
	advance(txt);
	len = find_rpar(txt);
	inter = ft_strndup(&txt->src[txt->i], 0, len - 1);
	if (!inter)
		return (NULL);
	txt->i += len + 1;
	node = ft_calloc(1, sizeof(t_ast_subshell));
	if (node)
	{
		node->kind = SUBSHELL;
		s_nbr_cmd = shell->nbr_cmd;
		shell->nbr_cmd = 0;
		node->inter = parse(inter, shell);
		shell->nbr_cmd = s_nbr_cmd;
	}
	free(inter);
	return ((t_ast *)node);
}
