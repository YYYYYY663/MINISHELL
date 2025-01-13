/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirect.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymizukam <ymizukam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 19:30:22 by teando            #+#    #+#             */
/*   Updated: 2025/01/05 03:31:55 by ymizukam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MISH_STREAM_H
# define MISH_STREAM_H

#include "mish_util.h"
#include <string.h>
# include <signal.h>

/*
** グローバル変数: シグナル状態を保持
** 0 = シグナル未受信
** SIGINT, SIGQUIT などのシグナル番号が入る
*/

/*
** シグナル初期化関数
*/
int	init_signals(void);


void		heredoc(const char *delimiter, int *in, t_info *info);

void		redirect_out(t_token_type type, char *file, int *out);

void		redirect_in(t_token_type type, char *file, int *in);

t_status	redirect_dipacher(t_list *list, int *in, int *out, t_info *info);

#endif /* MISH_STREAM_H */