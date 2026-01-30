/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 13:50:03 by rcompain          #+#    #+#             */
/*   Updated: 2026/01/30 15:08:38 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/mini_shell.h"

static void	dispatch_builtins(t_data *shell, t_ast *ast)
{
	t_ast_cmd	*cmd;

	if (ast->kind != CMD)
		return ;
	cmd = (t_ast_cmd *)ast;
	if (ft_strncmp(cmd->name, "echo", 4) == 0)
		echo_cmd(shell, cmd->args);
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

void	exec_line(t_data *shell, t_ast **ast)
{
	t_cmd	*cmds;
	int		i;

	cmds = init_cmds(shell, ast);
	if (!cmds)
		return ;
	i = 0;
	while (i < shell->nbr_cmd)
	{
		if (cmds[i].is_builtin == true)
			dispatch_builtins(shell, NULL);
		else
		{
				
		}
	}
}
