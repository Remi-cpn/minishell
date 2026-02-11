/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 15:28:20 by rcompain          #+#    #+#             */
/*   Updated: 2026/02/10 17:52:10 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/mini_shell.h"
#include <unistd.h>

static void	replace_pwd(t_data *shell, char *new_pwd, char *old_pwd)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (shell->env[i] && shell->exit_status != ERR_ALLOC && flag < 2)
	{
		if (ft_strncmp(shell->env[i], "OLDPWD=", 7) == 0)
		{
			free(shell->env[i]);
			shell->env[i] = ft_strjoin("OLDPWD=", old_pwd, 0, 0);
			if (!shell->env[i])
				shell->exit_status = ERR_ALLOC;
			flag++;
		}
		if (ft_strncmp(shell->env[i], "PWD=", 4) == 0)
		{
			free(shell->env[i]);
			shell->env[i] = ft_strjoin("PWD=", new_pwd, 0, 0);
			if (!shell->env[i])
				shell->exit_status = ERR_ALLOC;
			flag++;
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
		shell->exit_status = ERR_ALLOC;
		return ;
	}
	if (chdir(path) == -1)
	{
		free(old_pwd);
		shell->exit_status = ERR_ALLOC;
		return ;
	}
	new_pwd = getcwd(NULL, 0);
	if (!new_pwd)
	{
		free(old_pwd);
		shell->exit_status = ERR_ALLOC;
		return ;
	}
	replace_pwd(shell, new_pwd, old_pwd);
	free(new_pwd);
	free(old_pwd);
}

void	cd_cmd(t_data *shell, char **args)
{
	char	*path;

	shell->exit_status = SUCCES;
	if (!args[1])
	{
		path = get_env(shell, "HOME=");
		if (!path)
		{
			shell->exit_status = ERROR;
			return ;
		}
	}
	else
		path = args[1];
	if (args[1] && args[2])
	{
		shell->exit_status = ERROR;
		print_error("cd", NULL, 0, "too many arguments");
		return ;
	}
	cd_cmd_next(shell, path);
	if (shell->exit_status == ERR_ALLOC)
		print_error("cd", args[1], 0, NULL);
}
