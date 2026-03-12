/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_shell.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tseche <tseche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 18:35:36 by rcompain          #+#    #+#             */
/*   Updated: 2026/03/12 11:47:04 by tseche           ###   ########.fr       */
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
# include <stdio.h>

/** Readline */
# include <readline/history.h>
# include <readline/readline.h>

/** Mini_shell */
# include "ast.h"
# include "builtins.h"
# include "exit.h"
# include "ms_signals.h"
# include "pipeline.h"
# include "expand.h"

# define BOLD "\033[1m"
# define CYAN "\033[36m"
# define RESET "\033[0m"

/** Structs */
typedef struct s_data
{
	int		nbr_cmd;
	t_cmd	*cmds; // Pointeur pour free entre chaque readline
	char	*cmd_path;
	bool	exit;
	int		error_status;
	int		last_error_status;
	char	**env;
	int		need_cmd;
	int		*pid_adr;
	t_ast	**ast; // Poiteur pour free dans heredoc_child
	bool	is_child;
}	t_data;

/** Functions */
void	init_data(t_data *shell);
void	init_minimal_env(t_data *shell);
void	reset_line(t_data *shell);

#endif
