/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 11:26:56 by rcompain          #+#    #+#             */
/*   Updated: 2026/01/26 10:59:49 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/mini_shell.h"

/**
 * This function manages the program's output properly.
 */
void	exit_prog(t_data *shell)
{
	rl_clear_history();
	exit(shell->exit_status);
}
