/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 00:30:34 by rcompain          #+#    #+#             */
/*   Updated: 2026/03/05 17:49:07 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/mini_shell.h"
#include <dirent.h>
#include <string.h>

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
		add_tab_element(&new_args[i], cmd->args[i], flag);
	ft_memcpy(new_args + idx, add_args, len_add_args * sizeof(char *));
	i += len_add_args;
	while (*flag == SUCCES && cmd->args[++idx])
		add_tab_element(&new_args[i++], cmd->args[idx], flag);
	if (*flag == SUCCES)
	{
		cmd->args = new_args;
		free_array(tmp);
		free(add_args);
		return ;
	}
	free_array(new_args);
}

static int	cmp_with_key(char *s, char **key)
{
	int	i;
	int	j;

	if (!s || !s[0])
		return (0);
	if (ft_strncmp(s, key[0], ft_strlen(key[0])) != 0)
		return (0);
	i = ft_strlen(key[0]);
	j = 1;
	while (s[i] && key[j])
	{
		if (ft_strncmp(&s[i], key[j], ft_strlen(key[j])) == 0)
			j++;
		i++;
	}
	if ((key[j] && key[j][0] != '\0') || s[i] != '\0')
		return (0);
	return (1);
}

static void	list_files(char **new_args, char **key, char *arg, int *flag)
{
	DIR				*dir;
	struct dirent	*dirent;
	int				i;
	bool			all;

	all = false;
	if (strncmp(arg, ".*", 3) == 0)
		all = true;
	dir = opendir(".");
	if (!dir)
		return ;
	dirent = readdir(dir);
	if (!dirent)
		*flag = ERROR;
	i = 0;
	while (*flag == SUCCES && dirent)
	{
		if ((dirent->d_name[0] != '.' || all == true)
			&& cmp_with_key(dirent->d_name, key) == 1)
			add_tab_element(&new_args[i++], dirent->d_name, flag);
		dirent = readdir(dir);
	}
	closedir(dir);
}

void	wildcard(t_cmd *cmd)
{
	char	**key;
	int		idx;
	char	**add_args;
	int		nbr_files;
	int		flag;

	key = NULL;
	flag = 0;
	idx = find_arg_wc(cmd->args, &key);
	if (idx == FAILURE)
		return ;
	nbr_files = len_files(key);
	if (nbr_files == 0)
		return ;
	add_args = ft_calloc(nbr_files + 1, sizeof(char *));
	if (add_args)
	{
		list_files(add_args, key, cmd->args[idx], &flag);
		if (flag == SUCCES)
			replace_args(cmd, add_args, idx, &flag);
		else
			free_array(add_args);
	}
	free_array(key);
}
