/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 10:22:36 by rcompain          #+#    #+#             */
/*   Updated: 2026/01/30 20:56:43 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/mini_shell.h"
#include <fcntl.h>
#include <unistd.h>

int	test_path(t_data *shell, char *path, char **paths, char **cmd)
{
	int		find;
	char	*tmp;

	tmp = ft_strjoin(path, "/", 0, 0);
	tmp = ft_strjoin(tmp, cmd[0], 1, 0);
	find = access(tmp, X_OK);
	if (find == FAILURE)
	{
		ft_freenull(tmp);
		return (FAILURE);
	}
	shell->cmd_path = ft_strdup(tmp, 0);
	ft_freenull(tmp);
	if (!shell->cmd_path)
	{
		free_array(paths);
		exit_prog(shell, ERROR);
	}
	return (SUCCES);
}

int	find_path(t_data *shell, char **cmd)
{
	int		i;
	int		find;
	char	**paths;

	i = find_var(shell, "PATH", NULL);
	if (i == -1)
		return (-1);
	find = FAILURE;
	paths = ft_split(shell->env[i] + 5, ':');
	if (!paths)
		exit_prog(shell, ERR_ALLOC);
	i = 0;
	while (paths && paths[i] && find == FAILURE)
	{
		find = test_path(shell, paths[i], paths, cmd);
		i++;
	}
	free_array(paths);
	if (find == FAILURE)
		exit_prog(shell, ERROR);
	return (find);
}


