/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 14:57:49 by rcompain          #+#    #+#             */
/*   Updated: 2026/02/05 17:38:31 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/mini_shell.h"
#include <stdbool.h>

static t_cmd	*skip(t_cmd *cmds)
{
	cmds++;
	while (cmds && cmds->last_cmd == false)
		cmds++;
	return (cmds);
}

static t_cmd	*dispatch_exec(t_data *shell, t_cmd *cmds, bool *and_ok,
				bool *or_ok)
{
	pid_t	*pid;

	if (!cmds)
		return (NULL);
	if (shell->exit_status != ERROR && shell->nbr_cmd <= 1)
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
	ft_printf("cmds->next_and = %d | shell->exit.status = %d\n", cmds->next_and, shell->exit_status);
	if (cmds->next_and == true && shell->exit_status == SUCCES)
		*and_ok = true;
	if (cmds->next_or == true && shell->exit_status == SUCCES)
		*or_ok = true;
	write(2, "lala\n", 5);
	return (cmds);
}

void	exec(t_data *shell, t_ast **ast)
{
	t_cmd	*cmds;
	bool	and_ok;
	bool	or_ok;

	cmds = init_cmds(shell, ast);
	while (cmds->args && shell->exit == false)
	{
		and_ok = false;
		or_ok = false;
		cmds = dispatch_exec(shell, cmds, &and_ok, &or_ok);
		if (shell->exit_status == ERR_FORK || shell->exit_status == ERR_PIPE)
			return ;
		if (cmds->next_or == true && or_ok == true)
			cmds = skip(cmds);
		else if (cmds->next_and == true && and_ok == false)
			cmds = skip(cmds);
		else
			cmds++;
	}
}
