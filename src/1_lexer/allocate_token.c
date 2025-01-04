/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocate_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymizukam <ymizukam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 04:17:08 by teando            #+#    #+#             */
/*   Updated: 2025/01/05 03:37:25 by ymizukam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lexer.h"

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
