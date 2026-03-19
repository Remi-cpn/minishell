/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 15:28:20 by rcompain          #+#    #+#             */
/*   Updated: 2026/03/19 09:55:37 by rcompain         ###   ########.fr       */
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
	while (shell->env[i] && shell->error_status != ERR_ALLOC && flag < 2)
	{
		if (ft_strncmp(shell->env[i], "OLDPWD=", 7) == 0)
		{
			free(shell->env[i]);
			shell->env[i] = ft_strjoin("OLDPWD=", old_pwd, 0, 0);
			if (!shell->env[i])
				shell->error_status = ERR_ALLOC;
			flag++;
		}
		if (ft_strncmp(shell->env[i], "PWD=", 4) == 0)
		{
			free(shell->env[i]);
			shell->env[i] = ft_strjoin("PWD=", new_pwd, 0, 0);
			if (!shell->env[i])
				shell->error_status = ERR_ALLOC;
			flag++;
		}
		i++;
	}
}

static char	*set_new_pwd(t_data *shell, char *old_pwd, char *path)
{
	char	*new_pwd;

	shell->error_status = ERROR;
	if (strncmp(path, "..", 3) == 0)
		new_pwd = ft_strndup(old_pwd, 0, find_back(old_pwd) - 1);
	else
		new_pwd = ft_strdup(path, 0);
	if (!new_pwd)
		shell->error_status = ERR_ALLOC;
	return (new_pwd);
}

static void	cd_cmd_next(t_data *shell, char *path)
{
	char		*new_pwd;
	char		*old_pwd;

	old_pwd = getcwd(NULL, 0);
	if (!old_pwd)
		old_pwd = ft_strdup(get_env(shell, "PWD="), 0);
	if (!old_pwd)
		return ;
	if (old_pwd && chdir(path) == -1)
	{
		free(old_pwd);
		shell->error_status = ERROR;
		print_error("cd", path, 0, NULL);
		return ;
	}
	new_pwd = getcwd(NULL, 0);
	if (!new_pwd)
		print_error("cd", NULL, 0, "error retrieving current directory");
	if (!new_pwd)
		new_pwd = set_new_pwd(shell, old_pwd, path);
	if (new_pwd)
		replace_pwd(shell, new_pwd, old_pwd);
	free(new_pwd);
	free(old_pwd);
}

void	cd_cmd(t_data *shell, char **args)
{
	char	*path;

	shell->error_status = SUCCES;
	if (!args[1])
		path = get_env(shell, "HOME=");
	else if (args[1][0] == '-' && args[1][1] == '\0' &&
		!args[2])
		path = get_env(shell, "OLDPWD=");
	else
		path = args[1];
	if (!path)
	{
		shell->error_status = ERROR;
		print_error("cd", NULL, 0, "HOME not set");
		return ;
	}
	if (args[1] && args[2])
	{
		shell->error_status = ERROR;
		print_error("cd", NULL, 0, "too many arguments");
		return ;
	}
	cd_cmd_next(shell, path);
	if (shell->error_status == ERR_ALLOC)
		shell->error_status = ERROR;
}
