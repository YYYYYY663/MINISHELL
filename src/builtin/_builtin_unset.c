/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _builtin_unset.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymizukam <ymizukam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 22:13:06 by ymizukam          #+#    #+#             */
/*   Updated: 2025/01/14 12:42:52 by ymizukam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mish_builtin.h"

/**
 * @brief 環境変数を削除する（unsetコマンド）
 *
 * この関数は以下の処理を行います：
 * 1. 各引数に対して：
 *    - キーの妥当性をチェック
 *    - 無効なキーの場合はエラーメッセージを表示
 *    - 有効なキーの場合は環境変数を削除
 * 2. 全ての引数を処理した後、最後に発生したエラーを返す
 *
 * @param argv コマンド引数の配列（argv[0]はコマンド名）
 * @param info シェル情報構造体
 * @return t_status
 *    - E_NONE：正常終了
 *    - E_ENV_KEY：無効なキー名
 */
t_status	__unset(char **argv, t_info *info)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		lmap_unset(argv[i++], info->env_map, NULL);
	}
	return (E_NONE);
}
