/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tseche <tseche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 15:17:31 by tseche            #+#    #+#             */
/*   Updated: 2026/02/05 18:52:33 by tseche           ###   ########.fr       */
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

t_ast	*parse_expr(t_lookup *lookup, t_src_info *txt, t_data *shell)
{
	const t_token	tok = lexer(txt, shell);
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
	tmp = fn(txt, lookup[tok.kind].type, shell);
	if (!tmp)
		shell->exit_status = -1;
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
	tmp = parse_expr(lookup, txt, shell);
	if (!tmp)
	{
		free(node);
		return (NULL);
	}
	else if (tmp->kind == AND || tmp->kind == PIPE || tmp->kind == OR)
	{
		print_error(NULL, NULL, NULL, "Unexpected token");
		shell->exit_status = -1;
		return (NULL);
	}
	*node = tmp;
	if (tmp->kind == CMD)
		shell->nbr_cmd++;
	while (tmp->kind != END)
	{
		tmp = parse_expr(lookup, txt, shell);
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
