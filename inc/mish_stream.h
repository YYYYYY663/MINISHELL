/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mish_stream.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymizukam <ymizukam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 19:30:22 by teando            #+#    #+#             */
/*   Updated: 2025/01/14 12:59:49 by ymizukam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MISH_STREAM_H
# define MISH_STREAM_H

# include "mish_util.h"
# include <signal.h>
# include <string.h>

/*
** グローバル変数: シグナル状態を保持
** 0 = シグナル未受信
** SIGINT, SIGQUIT などのシグナル番号が入る
*/
volatile sig_atomic_t	g_signal_status;
/*
** シグナル初期化関数
*/

char					*read_command_line(const char *prompt);
int						is_quotes_balanced(const char *line);
char					*launch_readline(const char *prompt);

int						init_signals(void);

void					heredoc(const char *delimiter, int *in, t_info *info);

void					redirect_out(t_token_type type, char *file, int *out);

void					redirect_in(t_token_type type, char *file, int *in);

t_status				redirect_dipacher(t_list *list, int *in, int *out,
							t_info *info);

#endif /* MISH_STREAM_H */