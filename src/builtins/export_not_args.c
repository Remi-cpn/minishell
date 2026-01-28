/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_not_args.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 20:30:44 by rcompain          #+#    #+#             */
/*   Updated: 2026/01/28 21:56:46 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/mini_shell.h"

static void	print_env(char **env)
{
	int	i;
	int	j;

	i = 0;
	while (env[i])
	{
		write(1, "declare -x ", 11);
		j = 0;
		while (env[i][j] && env[i][j] != '=')
			write(1, &env[i][j++], 1);
		if (env[i][j] == '=')
		{
			write(1, "=\"", 2);
			j++;
			while (env[i][j])
				write(1, &env[i][j++], 1);
			write(1, "\"", 1);
		}
		write(1, "\n", 1);
		i++;
	}
}

static void	sort_env(char **env)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (env[i])
	{
		j = i + 1;
		while (env[j])
		{
			if (strkeycmp(env[i], env[j], '=') > 0)
			{
				tmp = env[i];
				env[i] = env[j];
				env[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

static char	**env_cpy(char **env)
{
	char	**env_cp;
	int		i;

	i = 0;
	while (env[i])
		i++;
	env_cp = ft_calloc(i + 1, sizeof(char *));
	if (!env_cp)
		return (NULL);
	i = 0;
	while (env[i])
	{
		env_cp[i] = ft_strdup(env[i], 0);
		if (!env_cp[i])
		{
			free_env(env_cp);
			return (NULL);
		}
		i++;
	}
	return (env_cp);
}

void	export_cmd_not_arg(t_data *shell)
{
	char	**env_cp;

	env_cp = env_cpy(shell->env);
	if (!env_cp)
	{
		call_to_exit(shell, ERR_ALLOC);
		return ;
	}
	sort_env(env_cp);
	print_env(env_cp);
	free_env(env_cp);
}
