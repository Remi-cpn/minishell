/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_shell.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 18:35:36 by rcompain          #+#    #+#             */
/*   Updated: 2026/01/25 16:02:44 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_SHELL_H
# define MINI_SHELL_H

/** Utils */
# include "../libft/libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>

/** Signals */
# include <signal.h>

/** Readline */
# include <readline/readline.h>
# include <readline/history.h>

/** Mini_shell */
# include "ms_functions.h"
# include "ms_structs_and_variables.h"
# include "ast.h"

#endif
