/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: von <von@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 14:05:55 by von               #+#    #+#             */
/*   Updated: 2026/03/11 22:22:00 by von              ###   ########.fr       */
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

//--------------------[EXPAND_DISPATCH.c]-------------
char	**dispatch_expand(char **args, t_data *shell, char **, int nbr_files);
void	dequote_range(char **, int start, int end);
char	*dequote(char **list);

//--------------------[LOGIC]----------------
char	**expand_all(char *string, t_data *shell);
int	    lenkey(char *str);
char	*resolve_key(char *str, int i, char **env, int *len);

//--------------------[SPLIT.c]----------------
char	**split_expand(char *str);
int     skip_pattern(char *str, char *p);

//--------------------[?.C]----------------
char	*question_mark(t_data *shell, char *arg, int *i);

//--------------------[EXPAND_HEREDOC.C]
char	*expand_all_heredoc(char *string, t_data *shell);

//--------------------[WILDCARD]----------------
int		wildcard(char **, int k, char **tmp, int nbr_files);
char	**replace_args(char **args, char **add_args, int idx, int *flag);
int		find_arg_wc(char **args, char ***key);
void	add_tab_element(char **new_arg, char *cmd_arg, int *flag);
int		ft_tablen(char **tab);
int		len_files(char **key);

#endif
