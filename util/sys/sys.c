/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sys.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymizukam <ymizukam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 16:33:27 by ymizukam          #+#    #+#             */
/*   Updated: 2025/01/14 12:36:19 by ymizukam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sys.h"
#include "token.h"
#include "xunistd.h"

extern volatile sig_atomic_t	g_signal_status;

/**
 * @brief シェルのメイン情報構造体を初期化する
 *
 * この関数は以下の初期設定を行います：
 * 1. メインのinfo構造体用にメモリを確保
 * 2. 提供された環境変数からenv_mapを作成
 * 3. カレントワーキングディレクトリを取得して保存
 * 4. 終了ステータス変数を0に初期化
 *
 * @param envp システムから提供される環境変数の配列
 * @return t_info* 初期化されたinfo構造体へのポインタ、失敗時はNULL
 */
t_info	*system_init(char **envp)
{
	t_info	*info;

	info = ft_calloc(sizeof(t_info), 1);
	if (!info)
		return (NULL);
	info->env_map = ft_list_from_strs(envp);
	if (getcwd(info->cwd, PATH_MAX) == NULL)
	{
		perror("pwd");
		system_exit(info, 1);
	}
	info->env_spc['?'] = ft_itoa(0);
	return (info);
}

/**
 * @brief 次の入力のためにコマンドライン状態を再初期化する
 *
 * この関数は以下のクリーンアップを行います：
 * 1. ソースライン用バッファを解放
 * 2. トークンリストが存在する場合はクリア
 * 3. AST構造体をクリア
 * 4. 終了ステータス変数を更新
 * 5. 次のコマンドのためにステータスを0にリセット
 *
 * @param info シェルのメイン情報構造体
 */
void	line_init(t_info *info)
{
	if (!info)
		exit(1);
	xfree((void **)&info->source_line);
	if (info->token_list != NULL)
	{
		ft_lstclear(&info->token_list, token_clear);
	}
	ast_clear(info->ast);
	info->ast = NULL;
	free(info->env_spc['?']);
	if (g_signal_status == SIGINT || g_signal_status == SIGQUIT)
		info->status = g_signal_status + 128;
#ifndef DEBUGOFF
	printf("status %d\n", info->status);
#endif
	info->env_spc['?'] = ft_itoa(info->status);
	g_signal_status = 0;
	info->status = 0;
}

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
	ft_lstclear(&info->alias, free);
	free(info);
	exit(status);
}
