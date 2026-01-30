/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 10:22:36 by rcompain          #+#    #+#             */
/*   Updated: 2026/01/30 15:09:04 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/mini_shell.h"
#include <fcntl.h>
#include <unistd.h>

static int	test_path(t_data *shell, char *path, char **paths, char **cmd)
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

static int	find_path(t_data *shell, char **cmd)
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

void	child_process(t_data *shell, char **cmd, int i, int pipes)
{
	int	find;
	int	j;

	find = find_path(shell, cmd);
	if (find == FAILURE)
	{
		shell->exit_status = ERROR;
		return ;
	}
	if ()

	dup2(pipex->fds[i - 1][0], STDIN_FILENO);
	dup2(pipex->fds[i][1], STDOUT_FILENO);
	j = 0;
	while (j < pipex->nbr_fds)
	{
		close(pipex->fds[j][0]);
		close(pipex->fds[j][1]);
		j++;
	}
	execve(pipex->path, pipex->cmd[i], pipex->envp);
	exit_prog(pipex, ERROR);
}
