/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 18:36:44 by rcompain          #+#    #+#             */
/*   Updated: 2026/01/25 12:03:50 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_shell.h"

#define BOLD  "\033[1m"
#define CYAN "\033[36m"
#define RESET "\033[0m"

int	main(void)
{
	char	*line;

	init_signals_prompt();
	while (1)
	{
		line = readline(CYAN BOLD "minishell 🐚: " RESET);
		if (!line || g_exit_flag == 1)
			exit_prog();
		add_history(line);
		free(line);
	}
	return (0);
}
