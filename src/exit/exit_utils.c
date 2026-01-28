/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 10:51:37 by rcompain          #+#    #+#             */
/*   Updated: 2026/01/28 22:04:31 by rcompain         ###   ########.fr       */
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

void	call_to_exit(t_data *shell, int status)
{
	shell->exit = true;
	shell->exit_status = status;
}

void	check_exit_flag(t_data *shell)
{
	if (g_exit_flag != 1)
		return ;
	shell->exit = true;
	shell->exit_status = SIGTERM_EXIT;
}
