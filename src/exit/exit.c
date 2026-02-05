/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 11:26:56 by rcompain          #+#    #+#             */
/*   Updated: 2026/02/05 17:29:48 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/mini_shell.h"
#include <errno.h>

/**
 * This function manages the program's output properly.
 */
void	exit_prog(t_data *shell, int status_error)
{
	if (status_error > 0)
		shell->exit_status = status_error;
	if (status_error < 0)
		errno = 1;
	free_env(shell->env);
	rl_clear_history();
	exit(status_error);
}
