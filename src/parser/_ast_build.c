/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_new.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymizukam <ymizukam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 20:12:26 by ymizukam          #+#    #+#             */
/*   Updated: 2025/01/05 21:54:01 by ymizukam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mish_parser.h"

/**
 * @brief 基本的なコマンド要素をパースしてASTノードを生成する
 * 
 * この関数は以下の処理を行います：
 * 1. 括弧で囲まれた式を処理（再帰的にexprを呼び出し）
 * 2. 括弧がない場合は単一のコマンドとしてパース
 * 3. コマンドの引数リストを消費して保存
 * 
 * @param list トークンリストのポインタ
 * @param info シェル情報構造体
 * @return t_ast* 生成されたASTノード
 */
t_ast	*primary(t_list **list, t_info *info)
{
	t_ast	*node;

	while (consume(TT_LPAREN, list))
	{
		node = expr(list, info);
		expect(TT_RPAREN, list);
		return (node);
	}
	node = ast_node_new(NT_CMD, NULL, NULL);
	node->args = consume_args(list);
	return (node);
}

/**
 * @brief パイプライン（コマンドの連鎖）をパースしてASTノードを生成する
 * 
 * この関数は以下の処理を行います：
 * 1. 最初のコマンドをパースしてパイプノードを作成
 * 2. パイプ記号が続く限り、新しいコマンドをパース
 * 3. 右側に連鎖的にパイプノードを追加
 * 
 * @param list トークンリストのポインタ
 * @param info シェル情報構造体
 * @return t_ast* パイプライン全体を表すASTノード
 */
t_ast	*pipeline(t_list **list, t_info *info)
{
	t_ast	*pipe_node;
	t_ast	*current_node;

	pipe_node = ast_node_new(NT_PIPE, primary(list, info), NULL);
	current_node = pipe_node;
	while (consume(PIPE, list))
	{
		current_node->right = ast_node_new(NT_PIPE, primary(list, info), NULL);
		current_node = current_node->right;
	}
	return (pipe_node);
}

/**
 * @brief 論理演算子（&&, ||）とセミコロンを含む式全体をパースする
 * 
 * この関数は以下の処理を行います：
 * 1. 最初のパイプラインをパース
 * 2. 論理演算子またはセミコロンが続く限り処理を継続
 * 3. 演算子の種類に応じて適切なノードタイプで結合
 *    - && → NT_AND
 *    - || → NT_OR
 *    - ;  → NT_EOF
 * 
 * @param list トークンリストのポインタ
 * @param info シェル情報構造体
 * @return t_ast* 式全体を表すASTノード
 */
t_ast	*expr(t_list **list, t_info *info)
{
	t_ast	*node;

	node = pipeline(list, info);
	while (1)
	{
		if (consume(TT_AND_AND, list))
		{
			node = ast_node_new(NT_AND, node, pipeline(list, info));
		}
		else if (consume(TT_OR_OR, list))
		{
			node = ast_node_new(NT_OR, node, pipeline(list, info));
		}
		else if (consume(TT_SEMICOLON, list))
		{
			node = ast_node_new(NT_EOF, node, pipeline(list, info));
		}
		else
		{
			break ;
		}
	}
	return (node);
}
