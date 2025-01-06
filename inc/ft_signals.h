/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signals.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 19:29:46 by teando            #+#    #+#             */
/*   Updated: 2024/12/17 19:30:16 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SIGNALS_H
# define FT_SIGNALS_H

# include "ft_system.h"
# include <signal.h>

/*
** グローバル変数: シグナル状態を保持
** 0 = シグナル未受信
** SIGINT, SIGQUIT などのシグナル番号が入る
*/
extern volatile sig_atomic_t g_signal_status;

/*
** シグナル初期化関数
*/
void	init_signals(void);

#endif