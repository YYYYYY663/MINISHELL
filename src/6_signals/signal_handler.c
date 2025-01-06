/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_setup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 01:35:45 by teando            #+#    #+#             */
/*   Updated: 2025/01/06 14:21:44 by teando           ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "ft_signals.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

/*
 * グローバル変数の定義
 */
volatile sig_atomic_t g_signal_status = 0;

/*
 * SIGINT (Ctrl+C) ハンドラ
 * シグナル受信を記録し、必要最小限の処理のみを行う
 */
static void sigint_handler(int signum)
{
	if (signum == SIGINT)
	{
		g_signal_status = SIGINT;
		write(STDOUT_FILENO, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

/*
 * SIGQUIT (Ctrl+\) ハンドラ
 * シグナル受信を記録するのみ
 */
static void sigquit_handler(int signum)
{
	if (signum == SIGQUIT)
		g_signal_status = SIGQUIT;
}

/*
 * シグナルハンドラの初期化
 */
void init_signals(void)
{
	struct sigaction sa_int;
	struct sigaction sa_quit;

	/* SIGINT の設定 */
	sa_int.sa_handler = sigint_handler;
	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_flags = 0;
	sigaction(SIGINT, &sa_int, NULL);

	/* SIGQUIT の設定 */
	sa_quit.sa_handler = sigquit_handler;
	sigemptyset(&sa_quit.sa_mask);
	sa_quit.sa_flags = 0;
	sigaction(SIGQUIT, &sa_quit, NULL);
}
