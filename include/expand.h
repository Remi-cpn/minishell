/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: von <von@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 14:05:55 by von               #+#    #+#             */
/*   Updated: 2026/03/05 18:22:08 by von              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_H
# define EXPAND_H

# include "mini_shell.h"
# include "./ast.h"

#define IFS " \t\n"

//--------------------[EXPAND.c]-------------
char	*get_env_key(char *str, char **env);
char    **expansion(char **args, t_data *shell);

//--------------------[LOGIC]----------------
char	**expand_all(char *string, t_data *shell);

//--------------------[SPLIT.c]----------------
char	**split_expand(char *str);

//--------------------[?.C]----------------
char	*question_mark(t_data *shell, char *arg);

//--------------------[WILDCARD]----------------
char	**wildcard(char **args);
int		find_arg_wc(char **args, char ***key);
void	add_tab_element(char **new_arg, char *cmd_arg, int *flag);
int		ft_tablen(char **tab);
int		len_files(void);
char	*strnstr_wich(char *big, char *little, size_t len);

#endif
