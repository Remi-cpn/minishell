/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_shell.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tseche <tseche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 18:35:36 by rcompain          #+#    #+#             */
/*   Updated: 2026/01/26 17:51:38 by tseche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_SHELL_H
# define MINI_SHELL_H

/** Utils */
# include "../libft/libft.h"
# include <stdbool.h>
# include <stdlib.h>
# include <unistd.h>

/** Signals */
# include <signal.h>

/** Readline */
# include <readline/history.h>
# include <readline/readline.h>

/** Mini_shell */
# include "ast.h"
# include "ms_functions.h"
# include "ms_structs_and_variables.h"

#endif
