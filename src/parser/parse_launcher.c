/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymizukam <ymizukam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 04:10:42 by teando            #+#    #+#             */
/*   Updated: 2025/01/05 21:57:57 by ymizukam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mish_parser.h"

/*
 * xlexer関数は、入力されたソースラインをトークン化し、その構文を検証します。
 *
 * 引数:
 * - info: 現在のシステム情報を保持するt_info構造体へのポインタ。トークンリストやステータスを管理します。
 *
 * 戻り値:
 * - トークン化および構文検証に成功した場合はE_NONEが返されます。
 * - エラーが発生した場合、対応するステータスがinfo->statusに設定され、同じ値が返されます。
 *
 * 処理の詳細:
 * 1. info->source_lineがNULLでないことを確認します。
 * 2. tokenize_line関数を呼び出してソースラインをトークン化します。
 * 3. トークン化に失敗した場合はステータスをE_SYNTAXに設定します。
 * 4. validate_syntax関数を呼び出して、得られたトークンの構文を検証します。
 * 5. すべての処理が成功した場合、E_NONEを返します。
 */
t_status	launch_lexer(t_info *info)
{
	info->token_list = NULL;
	info->status = E_NONE;
	if (!info->source_line)
		return (info->status);
	if (!tokenize_line(info))
	{
		if (info->status == E_NONE)
			info->status = E_SYNTAX;
		return (info->status);
	}
	if (!validate_syntax(info))
		return (info->status);
	return (info->status);
}



/**
 * @brief パーサーを起動し、トークンリストからASTを構築する
 * 
 * この関数は以下の処理を行います：
 * 1. トークンリストの先頭を保持
 * 2. 式全体をパースしてASTを生成
 * 3. 生成したASTをinfo構造体に保存
 * 
 * @param info シェル情報構造体（トークンリストとAST保存用）
 * @return t_status パース処理の結果（成功時はE_NONE）
 */
t_status	launch_parser(t_info *info)
{
	if (launch_lexer(info))
		return info->status;
	t_list	*head;

	head = info->token_list;
	info->ast = expr(&head, info);
	return (E_NONE);
}

