/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tseche <tseche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 18:36:44 by rcompain          #+#    #+#             */
/*   Updated: 2026/01/27 16:41:10 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_shell.h"

#define BOLD "\033[1m"
#define CYAN "\033[36m"
#define RESET "\033[0m"

int	main(void)
{
	char	*line;
	t_data	shell;

	init_signals_prompt();
	init_data(&shell);
	while (shell.exit == false)
	{
		line = readline("\001" CYAN BOLD "mini\002shell 🐚: \001" RESET "\002");
		if (!line || g_exit_flag == 1)
			exit_prog(&shell, 0);
		add_history(line);
		free(line);
	}
	exit_prog(&shell, 0);
	return (0);
}
