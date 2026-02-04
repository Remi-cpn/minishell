/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 10:51:37 by rcompain          #+#    #+#             */
/*   Updated: 2026/02/04 14:44:41 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/mini_shell.h"

void	print_error(char *name, char *arg, char c, char *msg)
{
	write(2, "minishell: ", 11);
	if (name)
	{
		write(2, name, ft_strlen(name));
		write(2, ": ", 2);
	}
	if (arg)
	{
		write(2, arg, ft_strlen(arg));
		write(2, ": ", 2);
	}
	if (c)
	{
		write(2, &c, 1);
		write(2, ": ", 2);
	}
	if (msg)
	{
		write(2, msg, ft_strlen(msg));
		write(2, "\n", 1);
	}
	else
		perror(NULL);
}

void	free_array(char **s)
{
	int	i;

	i = 0;
	while (s && s[i])
		ft_freenull(s[i++]);
	if (s)
		ft_freenull(s);
}

void	free_cmds(t_data *shell, t_cmd *cmds)
{
	int	i;

	i = 0;
	if (cmds)
	{
		while (cmds[i].args)
		{
			free_array(cmds[i].args);
			cmds[i].args = NULL;
			i++;
		}
		ft_freenull(cmds);
		cmds = NULL;
	}
	shell->nbr_cmd = 0;
}

void	free_env(char **env)
{
	int	i;

	if (!env)
		return ;
	i = 0;
	while (env[i])
	{
		free(env[i]);
		env[i] = NULL;
		i++;
	}
	free(env);
}

void	call_to_exit(t_data *shell, int status, char *msg)
{
	if (msg)
		write(2, msg, ft_strlen(msg));
	shell->exit = true;
	shell->exit_status = status;
}

void	check_exit_flag(t_data *shell)
{
	if (g_exit_flag != 1)
		return ;
	shell->exit = true;
	shell->exit_status = SIGTERM_EXIT;
}
