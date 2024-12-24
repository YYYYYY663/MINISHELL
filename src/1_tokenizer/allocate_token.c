/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocate_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 04:17:08 by teando            #+#    #+#             */
/*   Updated: 2024/12/23 20:28:41 by teando           ###   ########.fr       */
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

	tok = (t_token *)malloc(sizeof(t_token));//xmalloc
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

void	token_list_free(t_list **token_list)
{
	t_list	*cur;
	t_list	*nx;
	t_token	*tok;

	cur = *token_list;
	while (cur)
	{
		nx = cur->next;
		tok = (t_token *)cur->data;
		if (tok)
		{
			free(tok->value);
			free(tok);
		}
		free(cur);
		cur = nx;
	}
	*token_list = NULL;
}
