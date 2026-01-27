/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 13:38:56 by rcompain          #+#    #+#             */
/*   Updated: 2026/01/27 13:53:24 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/mini_shell.h"

void	pwd_cmd(t_data *shell)
{
	char	**env;
	int		i;

	env = __environ;
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PWD=", 4) == 0)
		{
			ft_printf("%s\n", env[i] + 4);
			return ;
		}
		i++;
	}
	shell->exit_status = ERR_PWD;
	write(2, "pwd: error retrieving current directory\n", 42);
}
