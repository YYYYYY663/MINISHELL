/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_traverse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymizukam <ymizukam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 16:28:15 by ymizukam          #+#    #+#             */
/*   Updated: 2025/01/29 19:14:41 by ymizukam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_executor.h"
#include "ft_parser.h"
#include "ft_system.h"
#include "ft_token.h"

// int			g_signal = 0;
extern volatile sig_atomic_t	g_signal_status;
/**
 * @brief 論理演算子ノード（&&, ||, ;）を実行する
 *
 * この関数は以下の処理を行います：
 * 1. AND演算子（&&）の場合：
 *    - 左側を実行し、成功時のみ右側を実行
 * 2. OR演算子（||）の場合：
 *    - 左側を実行し、失敗時のみ右側を実行
 * 3. セミコロン（;）の場合：
 *    - 左側と右側を順番に実行
 *
 * @param node 実行するASTノード
 * @param info シェル情報構造体
 * @return t_status 実行結果のステータスコード
 */
t_status	exec_connector(t_ast *node, t_info *info)
{
	if (node->ntype == NT_AND)
	{
		traverse_ast_nodes(node->left, info);
		if (!info->status)
			return (traverse_ast_nodes(node->right, info));
	}
	else if (node->ntype == NT_OR)
	{
		traverse_ast_nodes(node->left, info);
		if (info->status)
			return (traverse_ast_nodes(node->right, info));
	}
	else if (node->ntype == NT_EOF)
	{
		traverse_ast_nodes(node->left, info);
		printf("type %d\n", node->right->ntype);
		if (node->right)
			traverse_ast_nodes(node->right, info);
	}
	return (E_NONE);
}

/**
 * @brief ASTを再帰的に走査して実行する
 *
 * この関数は以下の処理を行います：
 * 1. シグナルの確認（中断要求があれば終了）
 * 2. パイプノードの場合：
 *    - パイプラインを実行
 *    - 全プロセスの終了を待機
 *    - 終了ステータスを環境変数に設定
 * 3. その他のノードは論理演算子として処理
 *
 * @param node 実行するASTノード
 * @param info シェル情報構造体
 * @return t_status 実行結果のステータスコード
 */
t_status	traverse_ast_nodes(t_ast *node, t_info *info)
{
	if (node == NULL)
		return (E_NONE);
	if (g_signal_status)
		return ((t_status)g_signal_status);
	if (node->ntype == NT_PIPE)
	{
		exec_pipeline(node, info);
		kill_pipeline(node, info);
		free(info->env_spc['?']);
		info->env_spc['?'] = ft_itoa(info->status);
		return (E_NONE);
	}
	return (exec_connector(node, info));
}
