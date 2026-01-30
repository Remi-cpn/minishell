/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 18:08:55 by rcompain          #+#    #+#             */
/*   Updated: 2026/01/30 14:41:45 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

typedef struct s_data	t_data;
typedef struct s_ast	t_ast;

/** Structs */
typedef struct s_exit
{
	bool	many_args;
	bool	not_num;
}	t_exit;

/** Functions */
void	echo_cmd(t_data *shell, char **args);
void	exit_cmd(t_data *shell, char **args);
void	pwd_cmd(t_data *shell, char **args);
void	env_cmd(t_data *shell, char **args);
void	cd_cmd(t_data *shell, char **args);
void	export_cmd(t_data *shell, char **args);
void	export_cmd_not_arg(t_data *shell);
void	unset_cmd(t_data *shell, char **args);

/** Utils */
char	*get_env(t_data *shell, char *key);
int		strkeycmp(const char *s1, const char *s2, char key);
int		find_var(t_data *shell, char *key, int *len_key);

#endif
