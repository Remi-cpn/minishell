/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: von <von@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 12:48:42 by tseche            #+#    #+#             */
/*   Updated: 2026/03/11 23:46:07 by von              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/mini_shell.h"
#include <stdlib.h>

char	*get_env_key(char *str, char **env)
{
	while (*env)
	{
		if ((ft_strncmp(str, *env, ft_strchr(*env, '=') - *env) == 0
			&& *(str + (ft_strchr(*env, '=') - *env)) == '\0'))
			return (ft_strchr(*env, '=') + 1);
		env++;
	}
	return (NULL);
}

char	**expansion(char **args, t_data *shell)
{
	char	**new;
	int		nbr_files;
	int		is_var;

	is_var = (args[0][0] == '$');
	nbr_files = len_files(NULL);
	new = ft_calloc(ft_tablen(args) + nbr_files + 1, sizeof(char *));
	if (!new)
		return (args);
	new = dispatch_expand(args, shell, new, nbr_files);
	free(args);
	if (new[0][0] == '\0' && is_var == 1)
	{
		free_array(new);
		return (NULL);
	}
	return (new);
}
