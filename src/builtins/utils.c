/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 18:10:33 by rcompain          #+#    #+#             */
/*   Updated: 2026/01/25 21:45:28 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/mini_shell.h"

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
