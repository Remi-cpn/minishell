/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 11:23:37 by rcompain          #+#    #+#             */
/*   Updated: 2026/02/07 18:24:57 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/mini_shell.h"

static int	export_with_value(t_data *shell, char *arg)
{
	int	idx;
	int	i;

	idx = find_var(shell, arg, NULL);
	if (idx == -1)
	{
		i = 0;
		while (shell->env[i])
			i++;
		shell->env = ft_realloc(shell->env, i + 1, i + 2, sizeof(char *));
		if (!shell->env)
			return (ERR_ALLOC);
		shell->env[i] = ft_strdup(arg, 0);
		if (!shell->env[i])
			return (ERR_ALLOC);
		shell->env[i + 1] = NULL;
	}
	else
	{
		free(shell->env[idx]);
		shell->env[idx] = ft_strdup(arg, 0);
		if (!shell->env[idx])
			return (ERR_ALLOC);
	}
	return (SUCCES);
}

static int	export_without_value(t_data *shell, char *arg)
{
	int	idx;
	int	i;
	int	len_key;

	len_key = 0;
	idx = find_var(shell, arg, &len_key);
	if (idx == -1)
	{
		i = 0;
		while (shell->env[i])
			i++;
		shell->env = ft_realloc(shell->env, i + 1, i + 2, sizeof(char *));
		if (!shell->env)
			return (ERR_ALLOC);
		if (arg[len_key] == '=')
			shell->env[i] = ft_strdup(arg, 0);
		else
			shell->env[i] = ft_strjoin(arg, "=", 0, 0);
		if (!shell->env[i])
			return (ERR_ALLOC);
		shell->env[i + 1] = NULL;
	}
	return (SUCCES);
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

static void	export_cmd_with_args(t_data *shell, char **args)
{
	bool	with_value;
	int		flag;
	int		i;

	i = 1;
	flag = 0;
	while (args[i])
	{
		with_value = true;
		if (arg_is_valid(&with_value, args[i]) == false)
		{
			shell->exit_status = ERROR;
			print_error("export", args[i], 0, "invalid arguments");
		}
		else if (with_value == true)
			flag = export_with_value(shell, args[i]);
		else
			flag = export_without_value(shell, args[i]);
		if (flag != 0)
			shell->exit_status = flag;
		i++;
	}
}

void	export_cmd(t_data *shell, char **args)
{
	shell->exit_status = SUCCES;
	if (!args[1])
		export_cmd_not_arg(shell);
	else
		export_cmd_with_args(shell, args);
	if (shell->exit_status == ERR_ALLOC)
		print_error("export", NULL, 0, NULL);
}
