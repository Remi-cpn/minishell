/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: von <von@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 00:30:34 by rcompain          #+#    #+#             */
/*   Updated: 2026/03/08 15:49:38 by von              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/mini_shell.h"
#include <dirent.h>
#include <string.h>

static char	**replace_args(char **args, char **add_args, int idx, int *flag)
{
	const int		len_cmd_args = ft_tablen(args);
	const int		len_add_args = ft_tablen(add_args);
	const char		**tmp = (const char **)args;
	char			**new_args;
	int				i;

	new_args = ft_calloc(len_cmd_args + len_add_args + 1, sizeof(char *));
	if (!new_args)
		return (NULL);
	i = -1;
	while (*flag == SUCCES && ++i < idx)
		add_tab_element(&new_args[i], args[i], flag);
	ft_memcpy(new_args + idx, add_args, len_add_args * sizeof(char *));
	i += len_add_args;
	while (*flag == SUCCES && args[++idx])
		add_tab_element(&new_args[i++], args[idx], flag);
	if (*flag == SUCCES)
	{
		args = new_args;
		free_array((char **)tmp);
		free(add_args);
		return (args);
	}
	free_array(new_args);
	return (NULL);
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
		{
			i += ft_strlen(key[j]);
			j++;
		}
		else
			i++;
	}
	if ((key[j] && key[j][0] != '\0')
		|| (s[i] != '\0' && key[j - 1][0] != '\0'))
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

static char	**wildcard_expand(char **args, int nbr_files)
{
	char	**key;
	int		idx;
	char	**add_args;
	int		flag;
	char	**res;

	flag = 0;
	res = args;
	key = NULL;
	idx = find_arg_wc(args, &key);
	if (nbr_files == 0)
		free(key);
	if (idx == FAILURE || nbr_files == 0)
		return (args);
	add_args = ft_calloc(nbr_files + 1, sizeof(char *));
	if (add_args)
	{
		list_files(add_args, key, args[idx], &flag);
		if (flag == SUCCES)
			res = replace_args(args, add_args, idx, &flag);
		else
			free_array(add_args);
	}
	free_array(key);
	return (res);
}

int	wildcard(char **new, int k, char **tmp, int nbr_files)
{
	char	**wild;
	int		count;
	int		j;

	wild = wildcard_expand(tmp, nbr_files);
	if (!wild)
	{
		free_array(tmp);
		return (-1);
	}
	count = ft_tablen(wild);
	j = 0;
	while (wild[j])
		new[k++] = wild[j++];
	free(wild);
	return (count);
}
