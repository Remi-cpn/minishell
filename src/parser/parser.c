/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tseche <tseche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 15:17:31 by tseche            #+#    #+#             */
/*   Updated: 2026/01/26 17:25:18 by tseche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "../../include/ast.h"
#include "../../libft/libft.h"

t_ast	*parse(char *src)
{
	char **env;

	env = ft_strdup(__environ, 0);
	
}