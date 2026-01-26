/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 18:36:44 by rcompain          #+#    #+#             */
/*   Updated: 2026/01/26 10:54:01 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_shell.h"

#define BOLD  "\033[1m"
#define CYAN "\033[36m"
#define RESET "\033[0m"

static void	init_data(t_data *shell)
{
	ft_memset(shell, 0, sizeof(t_data));
}

int	main(void)
{
	char	*line;
	t_data	shell;

	init_signals_prompt();
	init_data(&shell);
	while (shell.exit == false)
	{
		line = readline(CYAN BOLD "minishell 🐚: " RESET);
		if (!line)
			exit_prog(&shell);
		check_exit_flag(&shell);
		add_history(line);
		free(line);
	}
	exit_prog(&shell);
	return (0);
}
