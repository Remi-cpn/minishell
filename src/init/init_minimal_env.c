/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_minimal_env.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 16:33:00 by rcompain          #+#    #+#             */
/*   Updated: 2026/03/03 19:32:17 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/mini_shell.h"
#include <unistd.h>

static char	*get_home(t_data *shell)
{
	char	*home;
	int		i;
	int		count;

	home = getcwd(NULL, 0);
	if (!home)
		exit_prog(shell, ERR_ALLOC);
	i = -1;
	count = 0;
	while (count < 3)
	{
		i++;
		if (home[i] == '/')
			count++;
	}
	home[i] = '\0';
	return (home);
}

static char	*get_cwd(t_data *shell, char *name)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		exit_prog(shell, ERR_ALLOC);
	cwd = ft_strjoin(name, cwd, 0, 1);
	if (!cwd)
		exit_prog(shell, ERR_ALLOC);
	return (cwd);
}

void	init_minimal_env(t_data *shell)
{
	shell->env = ft_calloc(3, sizeof(char *));
	if (!shell->env)
		exit_prog(shell, ERR_ALLOC);
	shell->env[0] = get_cwd(shell, "OLDPDW=");
	shell->env[1] = get_cwd(shell, "PDW=");
	shell->env[2] = get_home(shell);
}
