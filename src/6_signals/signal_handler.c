/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 01:35:45 by teando            #+#    #+#             */
/*   Updated: 2025/01/20 08:26:54 by teando           ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "ft_signals.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>

volatile sig_atomic_t g_signal_status = 0;

int rl_noob(void)
{
	return (0);
}

static void sigint_handler(int signum)
{
	if (signum == SIGINT)
	{
		g_signal_status = SIGINT;
		rl_done = 1;
		rl_replace_line("", 0);
		write(STDOUT_FILENO, "\n", 1);
		rl_on_new_line();
	}
}

static void sigquit_handler(int signum)
{
	if (signum == SIGQUIT)
	{
		g_signal_status = SIGQUIT;
	}
}

int init_signals(void)
{
	struct sigaction sa_int;
	struct sigaction sa_quit;

	rl_event_hook = (rl_hook_func_t *)rl_noob;
	sa_int.sa_handler = sigint_handler;
	sa_int.sa_flags = SA_RESTART;
	sigemptyset(&sa_int.sa_mask);
	if (sigaction(SIGINT, &sa_int, NULL) == -1)
		return (-1);
	sa_quit.sa_handler = sigquit_handler;
	sa_quit.sa_flags = SA_RESTART;
	sigemptyset(&sa_quit.sa_mask);
	if (sigaction(SIGQUIT, &sa_quit, NULL) == -1)
		return (-1);
	return (0);
}
