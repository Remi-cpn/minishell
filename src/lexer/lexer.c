/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tseche <tseche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 16:01:12 by tseche            #+#    #+#             */
/*   Updated: 2026/01/25 16:11:46 by tseche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ast.h"
#include "../../libft/libft.h"

static t_token	token(char *src, t_token_type kind, int n)
{
	char	*tmp;
	
	tmp = ft_strndup(src, n);
	if (!tmp)
		return ((t_token){});
	return ((t_token){.value = src, .kind = kind});
}

t_token	lexer(char *src)
{
	if (ft_strncmp(src, "<<", 2) == 0)
		return (token(src, DINFTYPE, 2));
	else if (ft_strncmp(src, ">>", 2) == 0)
		return (token(src, DSUPTYPE, 2));
	else if (ft_strncmp(src, ">", 1) == 0)
		return (token(src, SUPTYPE, 1));
	else if (ft_strncmp(src, "<", 2) == 0)
		return (token(src, INFTYPE, 1));
}