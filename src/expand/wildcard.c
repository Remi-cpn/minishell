/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: von <von@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 00:30:34 by rcompain          #+#    #+#             */
/*   Updated: 2026/03/05 18:00:35 by von              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/mini_shell.h"
#include <dirent.h>
#include <string.h>

static char	**replace_args(char **args, char **add_args, int idx, int *flag)
{
	const int		len_cmd_args = ft_tablen(args);
	const int		len_add_args = ft_tablen(add_args);
	char			**tmp;
	char			**new_args;
	int				i;

	new_args = ft_calloc(len_cmd_args + len_add_args + 1, sizeof(char *));
	if (!new_args)
		return (NULL);
	tmp = args;
	i = -1;
	while (*flag == SUCCES && ++i <= idx)
		add_tab_element(&new_args[i], args[i], flag);
	ft_memcpy(new_args + idx, add_args, len_add_args * sizeof(char *));
	i += len_add_args;
	while (*flag == SUCCES && args[++idx])
		add_tab_element(&new_args[i++], args[idx], flag);
	if (*flag == SUCCES)
	{
		args = new_args;
		free_array(tmp);
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
			j++;
		i++;
	}
	if (key[j] && key[j][0] != '\0')
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

char	**wildcard(char	**args)
{
	char	**key;
	int		idx;
	char	**add_args;
	int		nbr_files;
	int		flag;
	char	**res;

	flag = 0;
	res = NULL;
	idx = find_arg_wc(args, &key);
	if (idx == -1)
		return (args);
	nbr_files = len_files();
	if (nbr_files == 0)
		return (args);
	add_args = ft_calloc(nbr_files + 1, sizeof(char *));
	if (!add_args)
		return (res);
	list_files(add_args, key, args[idx], &flag);
	free_array(key);
	if (flag == SUCCES)
		res =replace_args(args, add_args, idx, &flag);
	else
		free_array(add_args);
	return (res);
}
