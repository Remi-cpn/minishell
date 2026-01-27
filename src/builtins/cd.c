/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 15:28:20 by rcompain          #+#    #+#             */
/*   Updated: 2026/01/27 16:41:12 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/mini_shell.h"
#include <unistd.h>

static void	replace_pwd(t_data *shell, char *new_)

void	cd_cmd(t_data *shell, char **args)
{
	char	*path;
	char	*new_pwd;
	char	*old_pwd;

	old_pwd = getcwd(NULL, 0);
	if (!args || !args[0])
		chdir("/home");
	else
		chdir(args[0]);

	new_pwd = getcwd(NULL, 0);
	free(new_pwd);
	free(old_pwd);
}
