/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatch.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 16:01:39 by rcompain          #+#    #+#             */
/*   Updated: 2026/01/29 14:39:33 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/mini_shell.h"

void	dispatch_builtins(t_data *shell, t_ast *ast)
{
	t_ast_cmd	*cmd;

	if (ast->kind != CMD)
		return ;
	cmd = (t_ast_cmd *)ast;
	if (ft_strncmp(cmd->name, "echo", 4) == 0)
		echo_cmd(cmd->args);
	else if (ft_strncmp(cmd->name, "exit", 4) == 0)
		exit_cmd(shell, cmd->args);
	else if (ft_strncmp(cmd->name, "env", 3) == 0)
		env_cmd(shell, cmd->args);
	else if (ft_strncmp(cmd->name, "pwd", 3) == 0)
		pwd_cmd(shell, cmd->args);
	else if (ft_strncmp(cmd->name, "cd", 2) == 0)
		cd_cmd(shell, cmd->args);
	else if (ft_strncmp(cmd->name, "export", 6) == 0)
		export_cmd(shell, cmd->args);
	else if (ft_strncmp(cmd->name, "unset", 5) == 0)
		unset_cmd(shell, cmd->args);
}
