/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 00:30:34 by rcompain          #+#    #+#             */
/*   Updated: 2026/03/03 14:04:32 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/mini_shell.h"
#include <dirent.h>

static void	replace_args(t_cmd *cmd, char **add_args, int idx, int *flag)
{
	const int		len_cmd_args = ft_tablen(cmd->args);
	const int		len_add_args = ft_tablen(add_args);
	char			**tmp;
	char			**new_args;
	int				i;

	new_args = ft_calloc(len_cmd_args + len_add_args + 1, sizeof(char *));
	if (!new_args)
		return ;
	tmp = cmd->args;
	i = -1;
	while (*flag == SUCCES && ++i < idx)
	{
		new_args[i] = ft_strdup(cmd->args[i], 0);
		if (!new_args[i])
			*flag = ERR_ALLOC;
	}
	ft_memcpy(new_args + idx, add_args, len_add_args * sizeof(char *));
	i += len_add_args;
	while (*flag == SUCCES && cmd->args[++idx])
	{
		new_args[i] = ft_strdup(cmd->args[idx], 0);
		if (!new_args[i++])
			*flag = ERR_ALLOC;
	}
	if (*flag == SUCCES)
	{
		cmd->args = new_args;
		free_array(tmp);
	}
}

static void	list_files(char **new_args, char *key, int *flag)
{
	DIR				*dir;
	struct dirent	*dirent;
	int				i;

	dir = opendir(".");
	if (!dir)
		return ;
	dirent = readdir(dir);
	if (!dirent)
		return ;
	i = 0;
	while (*flag == SUCCES && dirent)
	{
		if (strnstr_wich(dirent->d_name, key, ft_strlen(dirent->d_name))
			&& dirent->d_name[0] != '.')
		{
			new_args[i] = ft_strdup(dirent->d_name, 0);
			if (!new_args[i])
				*flag = ERR_ALLOC;
			i++;
		}
		dirent = readdir(dir);
	}
	closedir(dir);
}

static int	find_arg_wc(char **args, char **key)
{
	int		i;
	char	*tmp;

	i = 0;
	while (args[i])
	{
		tmp = ft_strchr(args[i], '*');
		if (tmp)
		{
			*key = tmp + 1;
			return (i);
		}
		i++;
	}
	return (-1);
}

void	wildcard(t_cmd *cmd)
{
	char	*key;
	int		idx;
	char	**add_args;
	int		nbr_files;
	int		flag;

	key = NULL;
	flag = 0;
	idx = find_arg_wc(cmd->args, &key);
	if (idx == -1)
		return ;
	nbr_files = len_files();
	if (nbr_files == 0)
		return ;
	add_args = ft_calloc(nbr_files + 1, sizeof(char *));
	if (!add_args)
		return ;
	list_files(add_args, key, &flag);
	if (flag == SUCCES)
	{
		replace_args(cmd, add_args, idx, &flag);
		free(add_args);
	}
	else
		free_array(add_args);
}
