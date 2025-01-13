/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 22:16:26 by ymizukam          #+#    #+#             */
/*   Updated: 2025/01/09 05:33:21 by teando           ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "system.h"
#include "token.h"
#include "ast.h"
#include "xunistd.h"

/**
 * @brief 抽象構文木（AST）のノードとその子孫を再帰的に解放する
 * 
 * この関数は以下の処理を行います：
 * 1. 左右の子ノードを再帰的に解放
 * 2. ノードに関連する引数リストを解放
 * 3. ノード自体のメモリを解放
 * 
 * @param node 解放するASTノード
 */
void ast_clear(t_ast *node)
{
	if (node == NULL)
		return;
	ast_clear(node->left);
	ast_clear(node->right);
	if (node->args)
	{
		if (node->args->argv)
			ft_lstclear(&node->args->argv, token_clear);
		if (node->args->redr)
			ft_lstclear(&node->args->redr, token_clear);
		if (node->args->cargv)
			ft_strs_clear(node->args->cargv);
		xclose(&node->args->fds[0]);
		xclose(&node->args->fds[1]);
		if (node->args->pid != -1)
			waitpid(node->args->pid, NULL, 0);
		free(node->args);
	}
	free(node);
}


/**
 * @brief 新しい引数リスト構造体を作成する
 * 
 * この関数は以下の処理を行います：
 * 1. 引数リスト構造体用のメモリを確保
 * 2. 構造体を0で初期化
 * 3. リストとサイズを初期化
 * 
 * @return t_args* 初期化された引数リスト構造体、失敗時はNULL
 */
t_args *ast_args_new(void)
{
	t_args *args;

	args = ft_calloc(1, sizeof(t_args));
	if (args == NULL)
		return (NULL);
	args->fds[0] = -1;
	args->fds[1] = -1;
	args->pid = -1;
	return (args);
}

/**
 * @brief 新しいAST（抽象構文木）ノードを作成する
 * 
 * この関数は以下の処理を行います：
 * 1. ノード構造体用のメモリを確保
 * 2. ノードの種類と左右の子ノードを設定
 * 3. その他のフィールドを0で初期化
 * 
 * @param type ノードの種類（演算子や命令の種類）
 * @param left 左の子ノード
 * @param right 右の子ノード
 * @return t_ast* 初期化されたASTノード、失敗時はNULL
 */
t_ast *ast_node_new(int type, t_ast *left, t_ast *right)
{
	t_ast *node;

	node = ft_calloc(1, sizeof(t_ast));
	if (!node)
		return (NULL);
	node->ntype = type;
	node->left = left;
	node->right = right;
	return (node);
}

