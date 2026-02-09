/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_shell.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tseche <tseche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 18:35:36 by rcompain          #+#    #+#             */
/*   Updated: 2026/02/09 10:05:08 by tseche           ###   ########.fr       */
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
# include "pipeline.h"

/** Structs */
typedef struct s_data
{
	int		nbr_cmd;
	t_cmd	*cmds; // Pointeur pour free entre chaque readline
	char	*cmd_path;
	bool	exit;
	int		exit_status;
	char	**env;
	int		need_cmd;
}	t_data;

/** Functions */
void	init_data(t_data *shell);

//* TESTING */
void	print_cmd(t_cmd *cmd, int index);

#endif
