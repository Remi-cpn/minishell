/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 18:10:33 by rcompain          #+#    #+#             */
/*   Updated: 2026/01/28 21:23:22 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/mini_shell.h"

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

/**
 * This function checks if the char *arg is composed only of options.
 */
bool	check_is_options(char *arg, char *key)
{
	int	i;
	int	j;
	int	flag;

	i = 0;
	if (!arg[1])
		return (false);
	while (arg[++i])
	{
		j = 0;
		flag = 0;
		while (key[j] && flag == 0)
		{
			if (arg[i] == key[j])
				flag = 1;
			j++;
		}
		if (flag == 0)
			return (false);
	}
	return (true);
}
