/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 11:26:56 by rcompain          #+#    #+#             */
/*   Updated: 2026/02/09 16:13:38 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/mini_shell.h"

/**
 * This function manages the program's output properly.
 */
void	exit_prog(t_data *shell, int status_error)
{
	if (status_error < 0)
		status_error = 1;
	shell->error_status = status_error;
	if (shell->cmds)
		free_cmds(shell);
	free_array(shell->env);
	rl_clear_history();
	exit(status_error);
}
