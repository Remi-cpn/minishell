/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 14:56:58 by rcompain          #+#    #+#             */
/*   Updated: 2026/02/02 16:32:46 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/mini_shell.h"

static int	test_path(t_data *shell, char *path, char **paths, char **cmd)
{
	int		find;
	char	*tmp;

	tmp = ft_strjoin(path, "/", 0, 0);
	if (!tmp)
		return (ERR_ALLOC);
	tmp = ft_strjoin(tmp, cmd[0], 1, 0);
	if (!tmp)
		return (ERR_ALLOC);
	find = access(tmp, X_OK);
	if (find == FAILURE)
	{
		ft_freenull(tmp);
		return (FAILURE);
	}
	ft_freenull(shell->cmd_path);
	shell->cmd_path = ft_strdup(tmp, 0);
	ft_freenull(tmp);
	if (!shell->cmd_path)
		return (ERR_ALLOC);
	return (SUCCES);
}

static int	path_absolu(t_data *shell, char **cmd)
{
	if (access(cmd[0], F_OK) != 0)
	{
		write(2, "cmd: No such file or directory\n", 31);
		return (ERR_CMD_NOT_FOUND);
	}
	if (access(cmd[0], X_OK) != 0)
	{
		write(2, "cmd: Permission denied\n", 23);
		return (ERR_CMD_NOT_EXEC);
	}
	ft_freenull(shell->cmd_path);
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
	while (paths && paths[i] && find == FAILURE)
	{
		find = test_path(shell, paths[i], paths, cmd);
		i++;
	}
	free_array(paths);
	return (find);
}

int	find_path(t_data *shell, char **cmd)
{
	int		find;

	find = FAILURE;
	if (!ft_strchr(cmd[0], '/'))
		find = path_relatif(shell, cmd);
	else
		find = path_absolu(shell, cmd);
	if (find == ERR_CMD_NOT_FOUND)
		shell->exit_status = ERR_CMD_NOT_FOUND;
	if (find == ERR_CMD_NOT_EXEC)
		shell->exit_status = ERR_CMD_NOT_EXEC;
	if (find == ERR_ALLOC)
		call_to_exit(shell, ERR_ALLOC, NULL);
	if (find != SUCCES)
		return (FAILURE);
	return (SUCCES);
}
