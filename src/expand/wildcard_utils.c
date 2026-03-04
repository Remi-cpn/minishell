/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 11:12:55 by rcompain          #+#    #+#             */
/*   Updated: 2026/03/03 13:55:53 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/mini_shell.h"
#include <dirent.h>

char	*strnstr_wich(char *big, char *little, size_t len)
{
	size_t		i;
	size_t		len_little;
	const char	*p;

	i = 0;
	len_little = ft_strlen(little);
	if (little[0] == '\0')
		return ((char *)big);
	while (i < len && big[i])
	{
		p = &big[i];
		if (big[i] == little[0] && len_little <= len - i)
		{
			if (!ft_memcmp(p, little, len_little + 1))
				return ((char *)p);
		}
		i++;
	}
	return (NULL);
}

int	ft_tablen(char **tab)
{
	int	i;

	i = 0;
	while (tab && tab[i])
		i++;
	return (i);
}

int	len_files(void)
{
	DIR				*dir;
	struct dirent	*dirent;
	int				len;

	dir = opendir(".");
	if (!dir)
		return (0);
	len = 0;
	dirent = readdir(dir);
	if (!dirent)
		return (0);
	while (dirent)
	{
		len++;
		dirent = readdir(dir);
	}
	closedir(dir);
	return (len);
}
