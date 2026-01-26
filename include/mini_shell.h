/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_shell.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 18:35:36 by rcompain          #+#    #+#             */
/*   Updated: 2026/01/26 10:59:29 by rcompain         ###   ########.fr       */
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
# include "ast.h"
# include "builtins.h"
# include "exit.h"
# include "ms_signals.h"

/** Structs */
typedef struct s_data
{
	bool	exit;
	int		exit_status;
}	t_data;

#endif
