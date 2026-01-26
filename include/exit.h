/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 10:06:49 by rcompain          #+#    #+#             */
/*   Updated: 2026/01/26 10:59:41 by rcompain         ###   ########.fr       */
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

/** Builtins */
# define EXIT_TO_MANY_ARGS 1
# define EXIT_NUMERIC 2
# define ERR_BUILTINS 20

/** Signals (128 -> 159)*/
# define SIGINT_EXIT 130
# define SIGQUIT_EXIT 131
# define SIGTERM_EXIT 143

typedef struct s_data t_data;

/** Functions */
void	exit_prog(t_data *shell);
void	check_exit_flag(t_data *shell);
void	call_to_exit(t_data *shell, int status);

#endif