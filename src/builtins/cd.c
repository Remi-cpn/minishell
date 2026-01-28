/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 15:28:20 by rcompain          #+#    #+#             */
/*   Updated: 2026/01/28 10:37:02 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/mini_shell.h"
#include <unistd.h>

static void	replace_pwd(t_data *shell, char *new_pwd, char *old_pwd)
{
	int	i;

	i = 0;
	while (shell->env[i])
	{
		if (ft_strncmp(shell->env[i], "OLDPWD=", 7) == 0)
		{
			free(shell->env[i]);
			shell->env[i] = ft_strjoin("OLDPWD=", old_pwd, 0, 0);
			if (!shell->env[i])
				call_to_exit(shell, ERR_ALLOC);
		}
		if (ft_strncmp(shell->env[i], "PWD=", 4) == 0)
		{
			free(shell->env[i]);
			shell->env[i] = ft_strjoin("PWD=", new_pwd, 0, 0);
			if (!shell->env[i])
				call_to_exit(shell, ERR_ALLOC);
		}
		i++;
	}
}

static void	cd_cmd_next(t_data *shell, char *path)
{
	char		*new_pwd;
	char		*old_pwd;

	old_pwd = getcwd(NULL, 0);
	if (!old_pwd)
	{
		shell->exit_status = ERROR;
		return ;
	}
	if (chdir(path) == -1)
	{
		free(old_pwd);
		shell->exit_status = ERROR;
		return ;
	}
	new_pwd = getcwd(NULL, 0);
	if (!new_pwd)
	{
		free(old_pwd);
		shell->exit_status = ERROR;
		return ;
	}
	replace_pwd(shell, new_pwd, old_pwd);
	free(new_pwd);
	free(old_pwd);
}

void	cd_cmd(t_data *shell, char **args)
{
	char	*path;

	if (!args)
	{
		path = get_env(shell, "HOME=");
		if (!path)
		{
			shell->exit_status = ERROR;
			return ;
		}
	}
	else
		path = args[0];
	if (args && args[1])
	{
		shell->exit_status = ERROR;
		write(2, "bash: cd: too many args\n", 24);
		return ;
	}
	cd_cmd_next(shell, path);
}
