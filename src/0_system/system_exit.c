/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   system_exit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymizukam <ymizukam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 21:27:54 by teando            #+#    #+#             */
/*   Updated: 2025/02/12 18:49:21 by ymizukam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_system.h"
#include "xunistd.h"

/**
 * @brief シェルプログラムを終了し、全てのリソースを解放する
 *
 * この関数は以下のクリーンアップ処理を行います：
 * 1. 現在のコマンドライン状態を初期化/クリーンアップ
 * 2. env_spc配列に格納された全ての環境変数を解放
 * 3. 環境変数連結リスト（env_map）をクリア
 * 4. メインのinfo構造体を解放
 * 5. 指定されたステータスコードでプログラムを終了
 *
 * @param info シェルの全状態を含むメイン情報構造体
 * @param status システムに返す終了ステータスコード
 */
void	system_exit(t_info *info, t_status status)
{
	int	i;

	line_init(info);
	i = 0;
	while (i < 128)
		free(info->env_spc[i++]);
	ft_lstclear(&info->env_map, free);
	rl_clear_history();
	free(info);
	exit(status);
}
