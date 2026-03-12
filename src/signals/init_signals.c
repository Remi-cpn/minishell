/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_signals.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: von <von@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 11:46:38 by rcompain          #+#    #+#             */
/*   Updated: 2026/03/11 21:31:32 by von              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/mini_shell.h"

volatile sig_atomic_t	g_exit_flag = 0;

/**
 * This function ignores all signals during the execution of a child process.
 */
void	init_signals_parent(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_handler = SIG_IGN;
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}

/**
 * This function restores the default behavior of signals during the execution
 * of a child process.
 */
void	init_signals_child(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_handler = SIG_DFL;
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}

/**
 * This function redirects the signals to reproduce the behavior of bash.
 */
static void	handler_prompt(int sig)
{
	if (sig == SIGINT)
	{
		g_exit_flag = 130;
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
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
