/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 10:06:49 by rcompain          #+#    #+#             */
/*   Updated: 2026/02/03 10:54:12 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXIT_H
# define EXIT_H

/**----------> Error Code <----------**/
//(code free 10 -> 125)
# define SUCCES 0
# define ERROR 1
# define ERR_ALLOC 12

/** Commands */
# define ERR_CMD_NOT_EXEC 126
# define ERR_CMD_NOT_FOUND 127
# define ERR_PATH 125

/** Builtins */
# define EXIT_TO_MANY_ARGS 1
# define EXIT_NOT_NUMERIC 255
# define ERR_BUILTINS 20
# define ERR_PWD 21

/** Signals (128 -> 159)*/
# define SIGINT_EXIT 130
# define SIGQUIT_EXIT 131
# define SIGTERM_EXIT 143

typedef struct s_data	t_data;
typedef struct s_cmd	t_cmd;

/** Functions */
void	exit_prog(t_data *shell, int status_error);
void	check_exit_flag(t_data *shell);
void	call_to_exit(t_data *shell, int status, char *msg);
void	free_env(char **env);
void	free_array(char **s);
void	free_cmds(t_cmd *cmds);
void	print_error(char *name, char *arg, char c, char *msg);

#endif
