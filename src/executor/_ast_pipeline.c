/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _ast_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 02:46:04 by ymizukam          #+#    #+#             */
/*   Updated: 2025/01/09 05:41:42 by teando           ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "mish_executor.h"

/**
 * @brief パイプラインを実行する
 *
 * この関数は以下の処理を行います：
 * 1. 左側のノードがコマンドの場合：
 *    - パイプノードとして実行
 * 2. それ以外の場合：
 *    - 左側のノードを再帰的に処理
 *
 * @param node 実行するASTノード
 * @param info シェル情報構造体
 * @return t_status 実行結果のステータスコード
 */
t_status exec_pipeline(t_ast *node, t_info *info)
{
	if (node->left->ntype == NT_CMD)
		return (pipe_node(node, STDIN_FILENO, STDOUT_FILENO, info));
	else
		return (traverse_ast_nodes(node->left, info));
}

/**
 * @brief パイプライン内の全プロセスを終了する
 *
 * この関数は以下の処理を行います：
 * 1. 右側のノードを再帰的に処理
 * 2. コマンドノードの場合：
 *    - ファイルディスクリプタを閉じる
 *    - プロセスの終了を待機
 *    - PIDをリセット
 * 3. 左側のノードを再帰的に処理
 *
 * @param node 処理するASTノード
 * @param info シェル情報構造体
 */
void kill_pipeline(t_ast *node, t_info *info)
{
	(void)info;
	if (node == NULL)
		return;
	kill_pipeline(node->right, info);
	if (node->ntype == NT_CMD)
	{
		xclose(&node->args->fds[0]);
		xclose(&node->args->fds[1]);
		if (node->args->pid != -1)
			waitpid(node->args->pid, NULL, 0);
		node->args->pid = -1;
	}
	kill_pipeline(node->left, info);
}
