/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 14:56:58 by rcompain          #+#    #+#             */
/*   Updated: 2026/03/11 19:18:58 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/mini_shell.h"

static int	test_path(t_data *shell, char *path, char **cmd)
{
	int		find;
	char	*tmp;

	find = FAILURE;
	tmp = ft_strjoin(path, "/", 0, 0);
	if (!tmp)
		return (ERR_ALLOC);
	tmp = ft_strjoin(tmp, cmd[0], 1, 0);
	if (!tmp)
		return (ERR_ALLOC);
	if (cmd[0][0] != '\0')
		find = access(tmp, X_OK);
	if (find == FAILURE)
	{
		tmp = ft_freenull(tmp);
		return (ERR_CMD_NOT_FOUND);
	}
	shell->cmd_path = ft_freenull(shell->cmd_path);
	shell->cmd_path = ft_strdup(tmp, 0);
	tmp = ft_freenull(tmp);
	if (!shell->cmd_path)
		return (ERR_ALLOC);
	return (SUCCES);
}

static int	path_absolu(t_data *shell, char **cmd)
{
	if (access(cmd[0], F_OK) != 0)
	{
		print_error("cmd", cmd[0], 0, "no such file or directory");
		return (ERR_CMD_NOT_FOUND);
	}
	if (access(cmd[0], X_OK) != 0)
	{
		print_error("cmd", cmd[0], 0, "permission denied");
		return (ERR_CMD_NOT_EXEC);
	}
	shell->cmd_path = ft_freenull(shell->cmd_path);
	shell->cmd_path = ft_strdup(cmd[0], 0);
	if (!shell->cmd_path)
		return (ERR_ALLOC);
	return (SUCCES);
}

static int	path_relatif(t_data *shell, char **cmd)
{
	int		i;
	int		find;
	char	**paths;

	find = FAILURE;
	i = find_var(shell, "PATH", NULL);
	if (i == -1)
		return (ERR_CMD_NOT_FOUND);
	paths = ft_split(shell->env[i] + 5, ':');
	if (!paths)
		return (ERR_ALLOC);
	i = 0;
	while (paths && paths[i] && find != SUCCES)
	{
		find = test_path(shell, paths[i], cmd);
		i++;
	}
	free_array(paths);
	return (find);
}

/**
 * This function finds the path of the command to execute. It checks
 * if the command is an absolute path or a relative path and updates the 
 * shell's cmd_path accordingly.
 */
int	find_path(t_data *shell, char **cmd)
{
	int		find;

	find = FAILURE;
	if (!ft_strchr(cmd[0], '/'))
		find = path_relatif(shell, cmd);
	else
		find = path_absolu(shell, cmd);
	if (find == ERR_CMD_NOT_FOUND)
	{
		shell->error_status = ERR_CMD_NOT_FOUND;
		if (!ft_strchr(cmd[0], '/'))
			print_error("cmd", cmd[0], 0, "command not found");
	}
	if (find == ERR_CMD_NOT_EXEC)
		shell->error_status = ERR_CMD_NOT_EXEC;
	if (find == ERR_ALLOC)
		call_to_exit(shell, ERR_ALLOC, NULL);
	if (find != SUCCES)
		return (FAILURE);
	return (SUCCES);
}
