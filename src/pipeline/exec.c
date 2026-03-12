/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: von <von@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 14:57:49 by rcompain          #+#    #+#             */
/*   Updated: 2026/03/11 21:48:51 by von              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/mini_shell.h"
#include <stdbool.h>

static t_cmd	*skip(t_cmd *cmds, int kind)
{
	cmds++;
	while (cmds && cmds->last_cmd == false)
		cmds++;
	if (cmds && cmds->last_cmd == true && cmds->next_or == true && kind == OR)
		cmds = skip(cmds, OR);
	else if (cmds && cmds->last_cmd == true && cmds->next_or == false
		&& kind == OR)
		return (cmds + 1);
	if (cmds && cmds->last_cmd == true && cmds->next_and == true && kind == AND)
		cmds = skip(cmds, AND);
	else if (cmds && cmds->last_cmd == true && cmds->next_and == false
		&& kind == AND)
		return (cmds + 1);
	return (cmds);
}

static t_cmd	*dispatch_exec(t_data *shell, t_cmd *cmds, bool *and_ok,
		bool *or_ok)
{
	pid_t	*pid;

	if (!cmds)
		return (NULL);
	if (cmds->subshell)
		cmds = exec_subshell(shell, &cmds[0]);
	else if (cmds->last_cmd == true)
		cmds = exec_one_cmd(shell, &cmds[0]);
	else
	{
		pid = ft_calloc(shell->nbr_cmd, sizeof(pid_t));
		if (!pid)
		{
			call_to_exit(shell, ERR_ALLOC, NULL);
			return (NULL);
		}
		cmds = exec_pipeline(shell, cmds, pid);
		free(pid);
	}
	if (cmds->next_and == true && shell->error_status == SUCCES)
		*and_ok = true;
	if (cmds->next_or == true && shell->error_status == SUCCES)
		*or_ok = false;
	return (cmds);
}

static void	exec_loop(t_data *shell, t_cmd *cmds)
{
	bool	and_ok;
	bool	or_ok;

	while (cmds && (cmds->args || cmds->subshell) && shell->exit == false)
	{
		and_ok = false;
		or_ok = true;
		cmds = dispatch_exec(shell, cmds, &and_ok, &or_ok);
		if (shell->error_status == ERR_FORK || shell->error_status == ERR_PIPE)
			return ;
		if (cmds->next_or == true && or_ok == false)
			cmds = skip(cmds, OR);
		else if (cmds->next_and == true && and_ok == false)
			cmds = skip(cmds, AND);
		else
			cmds++;
	}
}

void	close_cmds_fds(t_data *shell)
{
	int	i;

	i = 0;
	while (i < shell->nbr_cmd)
	{
		if (shell->cmds[i].fd_in != STDIN_FILENO)
			close(shell->cmds[i].fd_in);
		if (shell->cmds[i].fd_out != STDOUT_FILENO)
			close(shell->cmds[i].fd_out);
		i++;
	}
}

void	exec(t_data *shell, t_ast **ast)
{
	t_cmd	*cmds;

	shell->ast = ast;
	cmds = init_cmds(shell, ast);
	if (!cmds)
		call_to_exit(shell, ERR_ALLOC, NULL);
	if (shell->error_status != SUCCES || g_exit_flag == 1)
	{
		g_exit_flag = 0;
		close_cmds_fds(shell);
		free_ast(ast);
		return ;
	}
	shell->error_status = shell->last_error_status;
	exec_loop(shell, cmds);
	close_cmds_fds(shell);
	free_ast(ast);
}
