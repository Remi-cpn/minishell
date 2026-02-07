/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_signals.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 11:28:40 by rcompain          #+#    #+#             */
/*   Updated: 2026/02/07 16:06:35 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_SIGNALS_H
# define MS_SIGNALS_H

# include <signal.h>

/** Variables */
extern volatile sig_atomic_t	g_exit_flag;

/** Functions */
void	init_signals_prompt(void);
void	init_signals_parent(void);
void	init_signals_child(void);

#endif
