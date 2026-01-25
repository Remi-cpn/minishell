/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 14:09:48 by rcompain          #+#    #+#             */
/*   Updated: 2026/01/25 15:52:24 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/mini_shell.h"

static void	echo(char **args)
{
	if (!option)
	{
		ft_printf("%s\n", txt);
		return ;
	}

}

void test_echo(t_ast *ast)
{
	if (ast->kind == PIPE)
		pipeline((t_ast_pipe *)ast)
	if (ast->kind == NORMAL)
		echo(((t_ast_normal *)ast)->args);
	echo();
}
