/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 13:50:03 by rcompain          #+#    #+#             */
/*   Updated: 2026/01/29 15:40:10 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/mini_shell.h"

void	exec_line(t_data *shell, t_ast **ast)
{
	t_ast	*tmp;

	tmp = ast[0];
	while (tmp && !shell->exit)
	{
		if (tmp->kind == CMD)
			dispatch_builtins(shell, tmp);
		tmp = tmp->next;
	}
}
