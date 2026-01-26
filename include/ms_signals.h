/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_signals.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 10:23:22 by rcompain          #+#    #+#             */
/*   Updated: 2026/01/26 10:26:03 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_SIGNALS_H
# define MS_SIGNALS_H

# include "mini_shell.h"
# include <signal.h>

/** Variables */
extern volatile sig_atomic_t	g_exit_flag;

/** Functions */
void	init_signals_prompt(void);

#endif