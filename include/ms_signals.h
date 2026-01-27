/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_signals.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tseche <tseche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 11:28:40 by rcompain          #+#    #+#             */
/*   Updated: 2026/01/27 17:11:34 by tseche           ###   ########.fr       */
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