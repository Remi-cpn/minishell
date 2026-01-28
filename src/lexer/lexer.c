/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tseche <tseche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 16:01:12 by tseche            #+#    #+#             */
/*   Updated: 2026/01/28 23:52:01 by tseche           ###   ########.fr       */
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

t_token	lexer(t_src_info txt)
{
	if (ft_strncmp(&txt.src[txt.i], "<<", 2) == 0)
		return (token(&txt.src[txt.i], DINFTYPE, 2));
	else if (ft_strncmp(&txt.src[txt.i], ">>", 2) == 0)
		return (token(&txt.src[txt.i], DSUPTYPE, 2));
	else if (ft_strncmp(&txt.src[txt.i], "&&", 2) == 0)
		return (token(&txt.src[txt.i], AMPERTYPE, 2));
	else if (ft_strncmp(&txt.src[txt.i], "||", 2) == 0)
		return (token(&txt.src[txt.i], VERBARTYPE, 2));
	else if (ft_strncmp(&txt.src[txt.i], ">", 1) == 0)
		return (token(&txt.src[txt.i], SUPTYPE, 1));
	else if (ft_strncmp(&txt.src[txt.i], "<", 1) == 0)
		return (token(&txt.src[txt.i], INFTYPE, 1));
	else if (ft_strncmp(&txt.src[txt.i], "\"", 1) == 0)
		return (token(&txt.src[txt.i], DQUOTETYPE, 1));
	else if (ft_strncmp(&txt.src[txt.i], "\'", 1) == 0)
		return (token(&txt.src[txt.i], SQUOTETYPE, 1));
	else if (ft_strncmp(&txt.src[txt.i], "(", 1) == 0)
		return (token(&txt.src[txt.i], LPARENTYPE, 1));
	else if (ft_strncmp(&txt.src[txt.i], ")", 2) == 0)
		return (token(&txt.src[txt.i], RPARENTYPE, 1));
	else if (ft_strncmp(&txt.src[txt.i], "$", 1) == 0)
		return (token(&txt.src[txt.i], DOLLARTYPE, 1));
	else if (ft_isalpha(&txt.src[txt.i]) || ft_isdigit(&txt.src[txt.i]))
		return (token(&txt.src[txt.i], WORDTYPE, len_word(&txt.src[txt.i])));
	//free_parsing, trow error "UNKNOWN CHARACTER"
}
