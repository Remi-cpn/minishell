/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: von <von@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 14:05:55 by von               #+#    #+#             */
/*   Updated: 2026/03/03 00:58:17 by von              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_H

# include "./ast.h"

//--------------------[EXPAND.c]-------------
t_ast    **dispatch_expand(t_ast **node, t_data *shell);
char	**join_dbchar(char **string, char **add, int *start, int *lenght);
char	*get_env_key(char *str, char **env);

//--------------------[LOGIC]----------------
char	*expand_all(char *string, t_data *shell);

//--------------------[UTILS]----------------
int	    node_string_is_none(t_ast *ast);
void	free_expand(char **s, int len, t_data *shell);
int 	dollar(char *string, char ***nv, int *thing, char **env);
int	    cp_raw(char ***nv, char *string, char find, int *thing);

#endif