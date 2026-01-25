/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 14:09:48 by rcompain          #+#    #+#             */
/*   Updated: 2026/01/25 15:09:20 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/mini_shell.h"

static void	echo(char *cmd, char *option, char *txt)
{
	if (!option)
	{
		ft_printf("%s\n", txt);
		return ;
	}

}

void test_echo(void)
{
	echo();
}
