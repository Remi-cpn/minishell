/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ?.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: von <von@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 00:06:28 by rcompain          #+#    #+#             */
/*   Updated: 2026/03/08 15:18:02 by von              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/mini_shell.h"

char	*question_mark(t_data *shell, char *arg, int *i)
{
	char	*s;
	int		len_s;
	char	*res;

	s = ft_itoa(shell->error_status);
	len_s = 0;
	if (s)
		len_s = ft_strlen(s);
	res = strndup(arg, *i);
	if (!s || !res)
	{
		shell->error_status = ERR_ALLOC;
		return (arg);
	}
	res = ft_strjoin(res, s, 1, 1);
	if (!res)
		return (NULL);
	s = &arg[*i + 2];
	*i += len_s;
	res = ft_strjoin(res, s, 1, 0);
	free(arg);
	return (res);
}
