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

#include "ft_system.h"
#include "ft_token.h"
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
 * @brief 引数を消費し、新しい引数リストを作成する
 *
 * この関数は以下の処理を行います：
 * 1. 新しい引数リスト構造体を作成
 * 2. CMD_ARG型のトークンのみを抽出
 * 3. トークンをコピーして新しいリストに追加
 *
 * @param lst 現在の引数リストの先頭を指すポインタ
 * @return t_args* 新しい引数リストの先頭を指すポインタ
 */
t_args *consume_args(t_list **lst)
{
	t_args *args;
	t_list *new_lst;
	t_token *token;
	t_token *cpy;

	args = ast_args_new();
	if (!args)
		return (NULL);
	token = (t_token *)(*lst)->data;
	while ((token->type & 0xF000) == CMD_ARG)
	{
		cpy = malloc(sizeof(t_token));
		cpy->type = token->type;
		cpy->value = ft_strdup(token->value);
		new_lst = ft_lstnew(cpy);
		if (token->type == TT_WORD)
			ft_lstadd_back(&args->argv, new_lst);
		if ((token->type & 0xF00) == REDIRECT)
			ft_lstadd_back(&args->redr, new_lst);
		(*lst) = (*lst)->next;
		token = (t_token *)(*lst)->data;
	}
	return (args);
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

/**
 * @brief 次のトークンが期待する種類の場合、トークンを消費する
 * 
 * この関数は以下の処理を行います：
 * 1. 現在のトークンの種類をチェック
 * 2. 期待する種類と一致する場合、トークンリストを進める
 * 
 * @param type 期待するトークンの種類
 * @param lst トークンリストのポインタ
 * @return int 消費に成功した場合は1、失敗した場合は0
 */
int consume(t_token_type type, t_list **lst)
{
	t_token *token;

	token = (t_token *)(*lst)->data;
	if (type != token->type)
		return (0);
	*lst = (*lst)->next;
	return (1);
}

/**
 * @brief 次のトークンが期待する種類であることを確認し、トークンを進める
 * 
 * この関数は以下の処理を行います：
 * 1. 現在のトークンの種類をチェック
 * 2. 期待する種類と一致しない場合は何もせずに返る
 * 3. 一致する場合はトークンリストを進める
 * 
 * @param type 期待するトークンの種類
 * @param lst トークンリストのポインタ
 */
void expect(t_token_type type, t_list **lst)
{
	t_token *token;

	token = (t_token *)(*lst)->data;
	if (type != token->type)
	{
		return;
	}
	*lst = (*lst)->next;
}
