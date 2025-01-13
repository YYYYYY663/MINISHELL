/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymizukam <ymizukam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 22:15:51 by ymizukam          #+#    #+#             */
/*   Updated: 2025/01/05 21:58:02 by ymizukam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "system.h"
#include "token.h"
#include "xunistd.h"


/**
 * @brief トークン構造体に関連する全てのメモリを解放する
 * 
 * この関数は以下の処理を行います：
 * 1. トークンの値文字列が存在する場合は解放
 * 2. トークン構造体自体を解放
 * トークンリスト操作のクリーンアップ関数として使用
 * 
 * @param ptr 解放するトークン構造体へのポインタ（互換性のためvoid*）
 */
void	token_clear(void *ptr)
{
	t_token	*token;

	token = (t_token *)ptr;
	if (token == NULL)
		return ;
	if (token->value)
		free(token->value);
	free(token);
}

/**
 * 指定されたトークンタイプと値を持つ新しいトークンを作成
 *
 * @param type トークンのタイプを指定する `t_token_type` 列挙型。
 * @param value トークンに関連付ける文字列値。
 * @param info メモリ確保のために使用されるシェルの状態情報。
 * @return 成功した場合は新しいトークンのポインタを返し、失敗した場合は `NULL` を返します。
 */
t_token	*create_token(t_token_type type, char *value, t_info *info)
{
	t_token	*tok;

	tok = (t_token *)xmalloc(sizeof(t_token), info);
	if (!tok)
		return (NULL);
	tok->type = type;
	tok->value = value;
	return (tok);
}

/**
 * トークンをトークンリストに追加
 *
 * @param info トークンリストを保持する `t_info` 構造体へのポインタ。
 * @param tok 追加するトークンを指す `t_token` 構造体へのポインタ。
 * @return 成功した場合は1を返し、失敗した場合は0を返します。
 */
int	add_token(t_info *info, t_token *tok)
{
	t_list	*node;
	t_list	*tmp;

	if (!tok)
		return (0);
	node = ft_lstnew(tok);
	if (!node)
	{
		free(tok->value);
		free(tok);
		return (0);
	}
	if (!info->token_list)
		info->token_list = node;
	else
	{
		tmp = info->token_list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = node;
	}
	return (1);
}
