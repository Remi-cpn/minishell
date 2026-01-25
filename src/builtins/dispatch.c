/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatch.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 16:01:39 by rcompain          #+#    #+#             */
/*   Updated: 2026/01/25 16:14:09 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/mini_shell.h"

void	dispatch_builtins(t_ast *ast)
{	
	t_ast_normal	*cmd;

	if (ast->kind != NORMAL)
		return ;
	cmd = (t_ast_normal *)ast;
	if (ft_strncmp(cmd->name, "echo", 4) == 0)
		echo(cmd->args);
}
