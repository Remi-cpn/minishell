/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tseche <tseche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 18:36:44 by rcompain          #+#    #+#             */
/*   Updated: 2026/03/12 18:04:53 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_shell.h"

int	main(void)
{
	char	*line;
	t_data	shell;
	t_ast	**node;

	init_signals_prompt();
	init_data(&shell);
	while (shell.exit == false)
	{
		line = readline("\001" CYAN BOLD "\002minishell: \001" RESET "\002");
		if (!line || g_exit_flag == 1)
			exit_prog(&shell, shell.last_error_status);
		if (line[0] == '\0')
			continue ;
		add_history(line);
		node = parse(line, &shell, 0);
		free(line);
		if (shell.error_status == SUCCES && node)
			exec(&shell, node);
		if (node)
			free_ast(node);
		reset_line(&shell);
	}
	exit_prog(&shell, shell.last_error_status);
	return (0);
}
