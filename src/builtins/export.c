/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 11:23:37 by rcompain          #+#    #+#             */
/*   Updated: 2026/02/03 11:28:22 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/mini_shell.h"

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
		if (shell->env)
			shell->env[i + 1] = ft_strdup(args[0], 0);
		if (!shell->env || !shell->env[i + 1])
			return (ERR_ALLOC);
	}
	else
	{
		free(shell->env[idx]);
		shell->env[idx] = ft_strdup(args[0], 0);
		if (!shell->env[idx])
			return (ERR_ALLOC);
	}
	return (SUCCES);
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
			return (ERR_ALLOC);
		if (args[0][len_key] == '=')
			shell->env[i + 1] = ft_strdup(args[0], 0);
		else
			shell->env[i + 1] = ft_strjoin(args[0], "=", 0, 0);
		if (!shell->env[i + 1])
			return (ERR_ALLOC);
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
			flag = export_with_value(shell, args);
		else
			flag = export_without_value(shell, args);
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
