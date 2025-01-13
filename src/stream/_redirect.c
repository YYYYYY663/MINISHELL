/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _redirect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymizukam <ymizukam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 03:30:18 by ymizukam          #+#    #+#             */
/*   Updated: 2025/01/05 21:54:50 by ymizukam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mish_stream.h"

/**
 * @brief 出力リダイレクトを設定する
 * 
 * この関数は以下の処理を行います：
 * 1. 既存の出力ファイルディスクリプタを閉じる
 * 2. リダイレクトの種類に応じてファイルを開く：
 *    - TT_REDIR_OUT (>)：新規作成または切り詰め
 *    - TT_APPEND (>>)：新規作成または追記
 * 3. パーミッション0644でファイルを作成
 * 
 * @param type リダイレクトの種類（TT_REDIR_OUT または TT_APPEND）
 * @param file 出力先のファイル名
 * @param out 標準出力のファイルディスクリプタ（更新される）
 */
void	redirect_out(t_token_type type, char *file, int *out)
{
	xclose(out);
	if (type == TT_REDIR_OUT)
	{
		*out = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	}
	if (type == TT_APPEND)
	{
		*out = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	}
}

/**
 * @brief 入力リダイレクトを設定する
 * 
 * この関数は以下の処理を行います：
 * 1. 既存の入力ファイルディスクリプタを閉じる
 * 2. 指定されたファイルを読み取り専用で開く
 * 
 * @param type リダイレクトの種類（TT_REDIR_IN）
 * @param file 入力元のファイル名
 * @param in 標準入力のファイルディスクリプタ（更新される）
 */
void	redirect_in(t_token_type type, char *file, int *in)
{
	xclose(in);
	if (type == TT_REDIR_IN)
	{
		*in = open(file, O_RDONLY);
	}
}
