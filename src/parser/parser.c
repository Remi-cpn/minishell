/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 15:17:31 by tseche            #+#    #+#             */
/*   Updated: 2026/02/04 21:32:17 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "../../include/ast.h"
#include "../../libft/libft.h"
#include "../../include/mini_shell.h"

char	**dup_env(void)
{
	char	**env;
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

t_ast	*parse_expr(t_lookup *lookup, t_src_info *txt)
{
	const t_token	tok = lexer(txt);
	t_look_handler	fn;
	t_ast			*tmp;
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
	{
		ft_putstr_fd("syntax error near unexpected token ", 2);
		ft_putchar_fd(txt->src[txt->i], 2);
		ft_putchar_fd('\n', 2);
	}
	return (tmp);
}

t_ast	**parse(char *src, char **env, t_data *shell)
{
	t_ast		**node;
	t_ast		*tmp;
	t_src_info	*txt;
	t_lookup	lookup[13];

	(void)env;
	gen_lookup(lookup);
	txt = ft_calloc(sizeof(t_src_info), 1);
	txt->src = src;
	txt->len = ft_strlen(src);
	node = ft_calloc(sizeof(t_list *), 1);
	if (!node)
		return (NULL);
	tmp = parse_expr(lookup, txt);
	if (!tmp)
	{
		free(node);
		return (NULL);
	}
	*node = tmp;
	if (tmp->kind == CMD)
		shell->nbr_cmd++;
	while (tmp->kind != END)
	{
		tmp = parse_expr(lookup, txt);
		if (!tmp)
			return (NULL);
		ft_lstadd_back((t_list **)node, (t_list *)tmp);
		if (!node)
			return (NULL);
		if (tmp->kind == CMD)
			shell->nbr_cmd++;
	}
	return (node);
}
