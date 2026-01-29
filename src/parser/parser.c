/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tseche <tseche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 15:17:31 by tseche            #+#    #+#             */
/*   Updated: 2026/01/29 16:51:59 by tseche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "../../include/ast.h"
#include "../../libft/libft.h"

char	**dup_env()
{
	char 	**env;
	int		i;

	i = 0;
	while (__environ[i] && i++)
		;
	env = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (__environ[i])
	{
		env[i] = ft_strdup(__environ[i], 0);
		if (!env[i++])
		{
			ft_freedb_ptr((void **)env);
			return (NULL);
		}
	}
	return (env);
}

t_ast	*addnode(t_ast *node, t_ast *tok, int i)
{
	t_ast	*tmp;

	tmp = node;
	node = ft_realloc(tmp, sizeof(t_ast) * (i + 1));
	free(tmp);
	if (!node)
		return (NULL);
	node[i + 1] = *tok;
	return (node);
}

t_ast	*parse_expr(t_lookup *lookup,t_src_info txt)
{
	const t_token	tok = lexer(txt);
	t_look_handler	fn;
	t_ast			*tmp;

	fn = lookup[tok.kind].fn;
	if (!fn)
		return (NULL);
	tmp = fn(txt);
	return (tmp);
}

t_ast	**parse(char *src, char **env)
{
	int			i;
	t_ast		**node;
	t_ast		*tmp;
	t_src_info	txt;
	t_lookup	lookup[13];

	(void)env;
	gen_lookup(lookup);
	i = 1;
	txt = (t_src_info){.src = src, .i = 0};
	node = malloc(sizeof(t_list *));
	if (!node)
		return (NULL);
	while (src)
	{
		tmp = parse_expr(lookup, txt);
		if (!tmp)
			return (NULL);
		ft_lstadd_back((t_list **)node, (t_list *)tmp);
		if (!node)
			return (NULL);
	}
	return (node);
}
