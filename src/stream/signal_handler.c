/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymizukam <ymizukam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 01:35:45 by teando            #+#    #+#             */
/*   Updated: 2025/01/14 12:56:31 by ymizukam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mish_stream.h"

/*
 * グローバル変数の定義
 */

/*
 * SIGINT (Ctrl+C) ハンドラ
 * シグナル受信を記録し、必要最小限の処理のみを行う
 */
static void	sigint_handler(int signum)
{
	if (signum == SIGINT)
	{
		g_signal_status = SIGINT;
		write(STDOUT_FILENO, "\n", 1);
		rl_on_new_line();
		rl_replace_line("\n", 0);
		rl_redisplay();
	}
}

/*
 * SIGQUIT (Ctrl+\) ハンドラ
 * シグナル受信を記録するのみ
 */
static void	sigquit_handler(int signum)
{
	if (signum == SIGQUIT)
		g_signal_status = SIGQUIT;
}

/*
 * シグナルハンドラの初期化
 */
int	init_signals(void)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

	/* SIGINT の設定 */
	sa_int.sa_handler = sigint_handler;
	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_flags = 0;
	if (!sigaction(SIGINT, &sa_int, NULL))
		return (-1);
	/* SIGQUIT の設定 */
	sa_quit.sa_handler = sigquit_handler;
	sigemptyset(&sa_quit.sa_mask);
	sa_quit.sa_flags = 0;
	if (!sigaction(SIGQUIT, &sa_quit, NULL))
		return (-1);
	return (0);
}
