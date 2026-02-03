/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 10:08:24 by rcompain          #+#    #+#             */
/*   Updated: 2026/02/03 11:28:38 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/mini_shell.h"

static void	remove_var(t_data *shell, char *arg)
{
	int	idx;

	idx = find_var(shell, arg, NULL);
	if (idx == -1)
		return ;
	free(shell->env[idx]);
	while (shell->env[idx + 1])
	{
		shell->env[idx] = shell->env[idx + 1];
		idx++;
	}
	shell->env[idx] = NULL;
}

static bool	arg_is_valid(char *arg)
{
	int	i;

	if (!(ft_isalpha(arg[0]) || arg[0] == '_'))
		return (false);
	i = 1;
	while (arg[i])
	{
		if (!(ft_isalnum(arg[i]) || arg[i] == '_'))
			return (false);
		i++;
	}
	return (true);
}

void	unset_cmd(t_data *shell, char **args)
{
	int	i;
	int	status;

	status = SUCCES;
	i = 1;
	while (args[i])
	{
		if (arg_is_valid(args[i]) == false)
		{
			status = ERROR;
			print_error("unset", args[i], 0, "not a valid identifier");
		}
		else
			remove_var(shell, args[i]);
		i++;
	}
	shell->exit_status = status;
}
