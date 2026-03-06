/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 11:12:55 by rcompain          #+#    #+#             */
/*   Updated: 2026/03/06 13:37:36 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/mini_shell.h"
#include <dirent.h>

void	add_tab_element(char **new_arg, char *cmd_arg, int *flag)
{
	*new_arg = ft_strdup(cmd_arg, 0);
	if (!*new_arg)
		*flag = ERR_ALLOC;
}

int	ft_tablen(char **tab)
{
	int	i;

	i = 0;
	while (tab && tab[i])
		i++;
	return (i);
}

int	len_files(char **key)
{
	DIR				*dir;
	struct dirent	*dirent;
	int				len;

	len = 0;
	dir = opendir(".");
	if (dir)
	{
		dirent = readdir(dir);
		while (dirent)
		{
			len++;
			dirent = readdir(dir);
		}
		closedir(dir);
	}
	if (len == 0 && key)
		free_array(key);
	return (len);
}
