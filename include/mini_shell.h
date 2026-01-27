/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_shell.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tseche <tseche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 18:35:36 by rcompain          #+#    #+#             */
/*   Updated: 2026/01/27 16:39:39 by rcompain         ###   ########.fr       */
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
# include "builtins.h"
# include "exit.h"
# include "ms_signals.h"

/** Structs */
typedef struct s_data
{
	bool	exit;
	int		exit_status;
	char	**env;
}	t_data;

/** Functions */
void	init_data(t_data *shell);

#endif
