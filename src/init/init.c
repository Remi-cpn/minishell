/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 15:46:25 by rcompain          #+#    #+#             */
/*   Updated: 2026/03/12 02:16:54 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/mini_shell.h"

void	init_env(t_data *shell)
{
	int	i;

	i = 0;
	while (__environ[i])
		i++;
	shell->env = ft_calloc(i + 1, sizeof(char *));
	if (!shell->env)
		exit_prog(shell, ERR_ALLOC);
	i = 0;
	while (__environ[i])
	{
		shell->env[i] = ft_strdup(__environ[i], 0);
		if (!shell->env[i])
			exit_prog(shell, ERR_ALLOC);
		i++;
	}
}

void	init_data(t_data *shell)
{
	ft_memset(shell, 0, sizeof(t_data));
	shell->nbr_cmd = 1;
	init_env(shell);
}
