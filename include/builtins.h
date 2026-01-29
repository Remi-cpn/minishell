/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 18:08:55 by rcompain          #+#    #+#             */
/*   Updated: 2026/01/29 10:04:14 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

typedef struct s_data	t_data;

/** Structs */
typedef struct s_echo
{
	bool	n;
	bool	e;
	bool	e_capital;
}	t_echo;

typedef struct s_exit
{
	bool	many_args;
	bool	not_num;
}	t_exit;

/** Functions */
void	dispatch_builtins(t_data *shell, t_ast *ast);
void	echo_cmd(char **args);
void	exit_cmd(t_data *shell, char **args);
void	pwd_cmd(t_data *shell, char **args);
void	env_cmd(t_data *shell, char **args);
void	cd_cmd(t_data *shell, char **args);
void	export_cmd(t_data *shell, char **args);
void	export_cmd_not_arg(t_data *shell);

/** Utils */
char	*get_env(t_data *shell, char *key);
bool	check_is_options(char *arg, char *key);
int		strkeycmp(const char *s1, const char *s2, char key);
int		find_var(t_data *shell, char *key, int *len_key);

#endif
