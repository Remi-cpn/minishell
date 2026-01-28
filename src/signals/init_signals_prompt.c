/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_signals_prompt.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tseche <tseche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 11:46:38 by rcompain          #+#    #+#             */
/*   Updated: 2026/01/27 17:11:40 by tseche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/mini_shell.h"

volatile sig_atomic_t	g_exit_flag = 0;

/**
 * This function redirects the signals to reproduce the behavior of bash.
 */
void	handler_prompt(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	// if (sig == SIGTERM)
	// 	g_exit_flag = 1;
	// if (sig == SIGCHLD)
	// {
	// 	//Fin de l'enfant.
	// 	return ;
	// }
}

/**
 * This function initiates signal management.
 */
void	init_signals_prompt(void)
{
	struct sigaction	sa;
	struct sigaction	sa_quit;

	sigemptyset(&sa.sa_mask);
	sa.sa_handler = handler_prompt;
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
	sigemptyset(&sa_quit.sa_mask);
	sa_quit.sa_handler = SIG_IGN;
	sa_quit.sa_flags = 0;
	sigaction(SIGQUIT, &sa_quit, NULL);
}
