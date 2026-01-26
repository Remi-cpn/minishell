/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tseche <tseche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 11:26:56 by rcompain          #+#    #+#             */
/*   Updated: 2026/01/26 17:56:54 by tseche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/mini_shell.h"

/**
 * This function manages the program's output properly.
 */
void	exit_prog(void)
{
	rl_clear_history();
	exit(1);
}
