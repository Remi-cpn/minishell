/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 18:36:44 by rcompain          #+#    #+#             */
/*   Updated: 2026/02/09 16:32:18 by rcompain         ###   ########.fr       */
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
	t_ast	**node;

	init_signals_prompt();
	init_data(&shell);
	while (shell.exit == false)
	{
		shell.need_cmd = 1;
		line = readline("\001" CYAN BOLD "mini\002shell 🐚: \001" RESET "\002");
		if (!line || g_exit_flag == 1)
			exit_prog(&shell, 0);
		add_history(line);
		node = parse(line, &shell);
		free(line);
		if (shell.exit_status == SUCCES && node)
		{
			ft_printf("Parsing done\n");
			exec(&shell, node);
		}
		reset_line(&shell);
	}
	exit_prog(&shell, 0);
	return (0);
}
