/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 11:26:56 by rcompain          #+#    #+#             */
/*   Updated: 2026/01/28 10:32:20 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/mini_shell.h"

void	free_env(char **env)
{
	int	i;

	if (!env)
		return ;
	i = 0;
	while (env[i])
	{
		free(env[i]);
		env[i] = NULL;
		i++;
	}
	free(env);
}

/**
 * This function manages the program's output properly.
 */
void	exit_prog(t_data *shell, int status_error)
{
	if (status_error != 0)
		shell->exit_status = status_error;
	free_env(shell->env);
	rl_clear_history();
	exit(shell->exit_status);
}
