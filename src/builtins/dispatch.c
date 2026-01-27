/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatch.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 16:01:39 by rcompain          #+#    #+#             */
/*   Updated: 2026/01/27 15:09:05 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/mini_shell.h"

void	dispatch_builtins(t_data *shell, t_ast *ast)
{
	t_ast_normal	*cmd;

	if (ast->kind != NORMAL)
		return ;
	cmd = (t_ast_normal *)ast;
	if (ft_strncmp(cmd->name, "echo", 4) == 0)
		echo_cmd(cmd->args);
	else if (ft_strncmp(cmd->name, "exit", 4) == 0)
		exit_cmd(shell, cmd->args);
	else if (ft_strncmp(cmd->name, "env", 3) == 0)
		env_cmd(shell, cmd->args);
	else if (ft_strncmp(cmd->name, "pwd", 3) == 0)
		pwd_cmd(shell, cmd->args);
}
