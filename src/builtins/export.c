/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 11:23:37 by rcompain          #+#    #+#             */
/*   Updated: 2026/01/28 22:03:13 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/mini_shell.h"

static int	find_var(t_data *shell, char *key, int *len_key)
{
	int		i;
	int		len;

	len = 0;
	while (key[len] && key[len] != '=')
		len++;
	if (len_key)
		*len_key = len;
	i = 0;
	while (shell->env[i])
	{
		if (ft_strncmp(shell->env[i], key, len) == 0)
		{
			if (shell->env[i][len] == '=')
				return (i);
		}
		i++;
	}
	return (-1);
}

static int	export_with_value(t_data *shell, char **args)
{
	int	idx;
	int	i;

	idx = find_var(shell, args[0], NULL);
	if (idx == -1)
	{
		i = 0;
		while (shell->env[i])
			i++;
		shell->env = ft_realloc(shell->env, i + 2);
		if (!shell->env)
			return (-1);
		shell->env[i + 1] = ft_strdup(args[0], 0);
		if (!shell->env[i + 1])
			return (-1);
	}
	else
	{
		free(shell->env[idx]);
		shell->env[idx] = ft_strdup(args[0], 0);
		if (!shell->env[idx])
			return (-1);
	}
	return (0);
}

static int	export_without_value(t_data *shell, char **args)
{
	int	idx;
	int	i;
	int	len_key;

	len_key = 0;
	idx = find_var(shell, args[0], &len_key);
	if (idx == -1)
	{
		i = 0;
		while (shell->env[i])
			i++;
		shell->env = ft_realloc(shell->env, i + 2);
		if (!shell->env)
			return (-1);
		if (args[0][len_key] == '=')
			shell->env[i + 1] = ft_strdup(args[0], 0);
		else
			shell->env[i + 1] = ft_strjoin(args[0], "=", 0, 0);
		if (!shell->env[i + 1])
			return (-1);
	}
	return (0);
}

static bool	arg_is_valid(bool *with_value, char *arg)
{
	int	i;

	if (!(ft_isalpha(arg[0]) || arg[0] == '_'))
		return (false);
	i = 1;
	while (arg[i] && arg[i] != '=')
	{
		if (!(ft_isalnum(arg[i]) || arg[i] == '_'))
			return (false);
		i++;
	}
	if (!arg[i])
		*with_value = false;
	return (true);
}

void	export_cmd(t_data *shell, char **args)
{
	bool	with_value;
	int		flag;

	if (!args || !args[0])
	{
		export_cmd_not_arg(shell);
		return ;
	}
	if (args[1])
	{
		shell->exit_status = ERROR;
		write(2, "export: too many args\n", 22);
		return ;
	}
	with_value = true;
	if (arg_is_valid(&with_value, args[0]) == false)
	{
		shell->exit_status = ERROR;
		write(2, "export: invalid args\n", 21);
		return ;
	}
	if (with_value == true)
		flag = export_with_value(shell, args);
	else
		flag = export_without_value(shell, args);
	if (flag == -1)
		call_to_exit(shell, ERR_ALLOC);
}
