/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 14:57:49 by rcompain          #+#    #+#             */
/*   Updated: 2026/02/07 15:45:44 by rcompain         ###   ########.fr       */
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
	if (shell->exit_status != ERROR && cmds->last_cmd == true)
		cmds = exec_one_cmd(shell, &cmds[0]);
	else if (shell->exit_status != ERROR)
	{
		pid = ft_calloc(shell->nbr_cmd, sizeof(pid_t));
		if (!pid)
		{
			call_to_exit(shell, ERR_ALLOC, NULL);
			return (NULL);
		}
		exec_pipeline(shell, cmds, pid);
	}
	if (cmds->next_and == true && shell->exit_status == SUCCES)
		*and_ok = true;
	if (cmds->next_or == true && shell->exit_status == SUCCES)
		*or_ok = false;
	return (cmds);
}

void	exec(t_data *shell, t_ast **ast)
{
	t_cmd	*cmds;
	bool	and_ok;
	bool	or_ok;

	cmds = init_cmds(shell, ast);
	if (!cmds)
		call_to_exit(shell, ERR_ALLOC, NULL);
	while (cmds && cmds->args && shell->exit == false)
	{
		and_ok = false;
		or_ok = true;
		cmds = dispatch_exec(shell, cmds, &and_ok, &or_ok);
		if (shell->exit_status == ERR_FORK || shell->exit_status == ERR_PIPE)
			return ;
		if (cmds->next_or == true && or_ok == false)
			cmds = skip(cmds, OR);
		else if (cmds->next_and == true && and_ok == false)
			cmds = skip(cmds, AND);
		else
			cmds++;
	}
}
