/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 14:05:55 by von               #+#    #+#             */
/*   Updated: 2026/03/05 11:54:10 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_H
# define EXPAND_H

# include "mini_shell.h"
# include "./ast.h"

//--------------------[EXPAND.c]-------------
t_ast	**dispatch_expand(t_ast **node, t_data *shell);
char	**join_dbchar(char **string, char **add, int *start, int *lenght);
char	*get_env_key(char *str, char **env);

//--------------------[LOGIC]----------------
char	*expand_all(char *string, t_data *shell);

//--------------------[UTILS]----------------
int		node_string_is_none(t_ast *ast);
void	free_expand(char **s, int len, t_data *shell);
int		dollar(char *string, char ***nv, int *thing, char **env);
int		cp_raw(char ***nv, char *string, char find, int *thing);

//--------------------[?]----------------
char	*question_mark(t_data *shell, char *arg);

//--------------------[WILDCARD]----------------
void	wildcard(t_cmd *cmd);
int		find_arg_wc(char **args, char ***key);
void	add_tab_element(char **new_arg, char *cmd_arg, int *flag);
int		ft_tablen(char **tab);
int		len_files(void);
char	*strnstr_wich(char *big, char *little, size_t len);

#endif
