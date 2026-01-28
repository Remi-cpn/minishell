/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 14:54:11 by rcompain          #+#    #+#             */
/*   Updated: 2026/01/27 16:05:53 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/mini_shell.h"

void	env_cmd(t_data *shell, char **args)
{
	int		i;

	i = 0;
	if (args || args[0])
	{
		shell->exit_status = ERR_CMD_NOT_FOUND;
		write(2, "env: too many arguments\n", 24);
		return ;
	}
	while (shell->env[i])
	{
		ft_printf("%s\n", shell->env[i]);
		i++;
	}
}
