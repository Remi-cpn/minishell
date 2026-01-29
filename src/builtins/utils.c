/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 18:10:33 by rcompain          #+#    #+#             */
/*   Updated: 2026/01/29 11:22:35 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/mini_shell.h"

/**
 * Allows you to find a variable in env and to modify the size of the 
 * variable name.
 */
int	find_var(t_data *shell, char *key, int *len_key)
{
	int		i;
	int		len;

	len = 0;
	while (key[len] && key[len] != '=')
		len++;
	if (len_key)
		*len_key = len;
	i = 0;
	while (shell->env[i])
	{
		if (ft_strncmp(shell->env[i], key, len) == 0)
		{
			if (shell->env[i][len] == '=')
				return (i);
		}
		i++;
	}
	return (-1);
}

/**
 * The same as strncmp except that it compares up to a given character or 
 * until the end.
 */
int	strkeycmp(const char *s1, const char *s2, char key)
{
	size_t	i;

	i = 0;
	if (!key)
		return (0);
	while (s1[i] && s1[i] != key && s2[i] && s2[i] != key && s1[i] == s2[i])
		i++;
	return (((unsigned char)s1[i]) - ((unsigned char)s2[i]));
}

/**
 * This function returns the line in the environment starting with the key. 
 * Be careful to enter = with key.
 */
char	*get_env(t_data *shell, char *key)
{
	int		i;
	size_t	len_key;
	char	*tmp;

	if (!key)
		return (NULL);
	len_key = ft_strlen(key);
	i = 0;
	while (shell->env[i])
	{
		if (ft_strncmp(shell->env[i], key, len_key) == 0)
		{
			tmp = shell->env[i];
			tmp += len_key;
			return (tmp);
		}
		i++;
	}
	return (NULL);
}

