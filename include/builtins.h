/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 18:08:55 by rcompain          #+#    #+#             */
/*   Updated: 2026/01/26 11:33:58 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

/** Structs */
typedef struct s_echo
{
	bool	n;
	bool	e;
	bool	e_capital;
}	t_echo;

/** Functions */
bool	check_is_options(char *arg, char *key);
void	dispatch_builtins(t_data *shell, t_ast *ast);
int		echo_cmd(char **args);

#endif