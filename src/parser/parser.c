/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tseche <tseche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 15:17:31 by tseche            #+#    #+#             */
/*   Updated: 2026/01/28 17:16:15 by tseche           ###   ########.fr       */
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
	t_token	*tmp;

	tmp = node;
	node = ft_realloc(tmp, sizeof(t_ast) * (i + 1));
	free(tmp);
	if (!node);
		return (NULL);
	node[i + 1] = *tok;
	return (node);
}

t_ast	*parse(char *src)
{
	char	**env;
	int		i;
	t_ast	*node;
	t_ast	*tmp;

	env = dup_env();
	gen_lookup();
	i = 1;
	node = parse_expr(src);
	while (src)
	{
		tmp = parse_expr(src);
		if (tmp == 0)
			return (NULL);
		node = addnode(node, tmp, i);
		if (!node)
			return (NULL);
	}
	return (&node);
}