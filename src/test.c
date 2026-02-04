/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 14:38:34 by rcompain          #+#    #+#             */
/*   Updated: 2026/02/04 14:46:04 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_shell.h"

void	print_cmd(t_cmd *cmd, int index)
{
	int	i;
    ft_printf("=== CMD [%d] ===\n", index);
    ft_printf("  is_builtin: %d\n", cmd->is_builtin);
    ft_printf("  args: %p\n", cmd->args);
    if (cmd->args && cmd->args[0])
	{
		i = 0;
		while (cmd->args[i])
		{
			ft_printf("    args[%d]: %s\n", i, cmd->args[i]);
			i++;
		}
		ft_printf("    args[%d]: %s\n", i, cmd->args[i]);
	}
    ft_printf("  fd_in: %d | fd_out: %d\n", cmd->fd_in, cmd->fd_out);
    ft_printf("  last_cmd: %d | next_or: %d | next_and: %d\n", 
        cmd->last_cmd, cmd->next_or, cmd->next_and);
    ft_printf("\n");
}