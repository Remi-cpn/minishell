/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ?.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 00:06:28 by rcompain          #+#    #+#             */
/*   Updated: 2026/03/03 00:16:40 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/mini_shell.h"

char	*question_mark(t_data *shell, char *arg)
{
	char	*s;

	s = ft_itoa(shell->error_status);
	if (!s)
	{
		shell->error_status = ERR_ALLOC;
		return (arg);
	}
	free(arg);
	return (s);
}
