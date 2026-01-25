/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_functions.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 11:28:40 by rcompain          #+#    #+#             */
/*   Updated: 2026/01/25 16:10:57 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_FUNCTIONS_H
# define MS_FUNCTIONS_H

# include "mini_shell.h"

/** init_signals.c */
void	init_signals_prompt(void);

/** builtins */
void	dispatch_builtins(t_ast *ast);
void	echo(char **args);

/** exit.c */
void	exit_prog(void);

#endif
