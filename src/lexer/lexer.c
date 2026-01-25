/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tseche <tseche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 16:01:12 by tseche            #+#    #+#             */
/*   Updated: 2026/01/25 16:46:07 by tseche           ###   ########.fr       */
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

int	len_word(char *src)
{
	int	i;

	i = 0;
	if ((src[i] >= 'A' && src[i] <= 'Z') || (src[i] >= 'a' && src[i] <= 'z'))
	{
		while ((src[i] >= 'A' && src[i] <= 'Z')
			|| (src[i] >= 'a' && src[i] <= 'z')
			|| src[i] == '_')
			i++;
	}
	else
	{
		while ((src[i] >= '0' && src[i] <= '9'))
			i++;
	}
	return (i);
}

t_token	lexer(char *src)
{
	if (ft_strncmp(src, "<<", 2) == 0)
		return (token(src, DINFTYPE, 2));
	else if (ft_strncmp(src, ">>", 2) == 0)
		return (token(src, DSUPTYPE, 2));
	else if (ft_strncmp(src, "&&", 2) == 0)
		return (token(src, AMPERTYPE, 2));
	else if (ft_strncmp(src, "||", 2) == 0)
		return (token(src, VERBARTYPE, 2));
	else if (ft_strncmp(src, ">", 1) == 0)
		return (token(src, SUPTYPE, 1));
	else if (ft_strncmp(src, "<", 1) == 0)
		return (token(src, INFTYPE, 1));
	else if (ft_strncmp(src, "\"", 1) == 0)
		return (token(src, DQUOTETYPE, 1));
	else if (ft_strncmp(src, "\'", 1) == 0)
		return (token(src, SQUOTETYPE, 1));
	else if (ft_strncmp(src, "(", 1) == 0)
		return (token(src, LPARENTYPE, 1));
	else if (ft_strncmp(src, ")", 2) == 0)
		return (token(src, RPARENTYPE, 1));
	else if (ft_strncmp(src, "$", 1) == 0)
		return (token(src, DOLLARTYPE, 1));
	else if ((src[0] >= 'A' && src[0] <= 'Z') || (src[0] >= 'a' && src[0] <= 'z') || (src[0] >= '0' && src[0] <= '9'))
		return (token(src, WORDTYPE, len_word(src)));
	//free_parsing, trow error "UNKNOWN CHARACTER"
}
