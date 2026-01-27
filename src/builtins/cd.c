/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 15:28:20 by rcompain          #+#    #+#             */
/*   Updated: 2026/01/27 15:58:45 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/mini_shell.h"
#include <unistd.h>

void	cd_cmd()
{
	char	*path;
	char	*new_pwd;
	char	*old_pwd;


	old_pwd = getcwd(NULL, 0);
	chdir(const char *path);
	new_pwd = getcwd(NULL, 0);
	PWD 

}
