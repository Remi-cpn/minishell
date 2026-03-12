/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils_sub.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: von <von@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 09:59:24 by rcompain          #+#    #+#             */
/*   Updated: 2026/03/12 02:23:36 by von              ###   ########.fr       */
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
	char			*inter;
	t_token			token;
	int				s_nbr_cmd;

	token = advance(txt, shell);
	free(token.value);
	len = find_rpar(txt);
	inter = ft_strndup(&txt->src[txt->i], 0, len - 1);
	if (!inter)
		return (NULL);
	txt->i += len + 1;
	node = ft_calloc(1, sizeof(t_ast_subshell));
	if (node)
	{
		node->kind = kind;
		s_nbr_cmd = shell->nbr_cmd;
		shell->nbr_cmd = 0;
		node->inter = parse(inter, shell);
		node->nbr_cmd = shell->nbr_cmd;
		shell->nbr_cmd = s_nbr_cmd;
	}
	free(inter);
	return ((t_ast *)node);
}
