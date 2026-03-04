/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tseche <tseche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 14:05:55 by von               #+#    #+#             */
/*   Updated: 2026/03/04 11:45:33 by tseche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_H
# define EXPAND_H

# include "mini_shell.h"
# include "./ast.h"

#define IFS " \t\n"

//--------------------[EXPAND.c]-------------
char	*get_env_key(char *str, char **env);

//--------------------[LOGIC]----------------
char	**expand_all(char *string, t_data *shell);

//--------------------[UTILS]----------------

//--------------------[?]----------------
char	*question_mark(t_data *shell, char *arg);

//--------------------[WILDCARD]----------------
void	wildcard(t_cmd *cmd);
int		ft_tablen(char **tab);
int		len_files(void);
char	*strnstr_wich(char *big, char *little, size_t len);

#endif
