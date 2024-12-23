/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_syntax.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 14:02:42 by teando            #+#    #+#             */
/*   Updated: 2024/12/23 14:09:01 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lexer.h"

/*
** ------------------------------------------------------------
** 1) 括弧の対応チェック (単純なカウントによる整合性チェック)
** ------------------------------------------------------------
*/
static int	check_parentheses(t_list *lst, t_info *info)
{
	int		count;
	t_token	*tok;

	count = 0;
	while (lst)
	{
		tok = (t_token *)lst->data;
		if (tok->type == TT_LPAREN)
			count++;
		else if (tok->type == TT_RPAREN)
			count--;
		if (count < 0)
		{
			info->status = E_SYNTAX;
			return (0);
		}
		lst = lst->next;
	}
	if (count != 0)
	{
		info->status = E_SYNTAX;
		return (0);
	}
	return (1);
}

/*
** ------------------------------------------------------------
** 2) 隣接トークンの整合性チェック
**    - 不正な演算子の連続 (| |、&& && 等)
**    - リダイレクトにファイル名がない
**    - 行頭/行末に不正トークン
** ------------------------------------------------------------
*/
static int	check_adjacency(t_list *lst, t_info *info)
{
	t_token	*prev;
	t_token	*curr;

	prev = NULL;
	while (lst)
	{
		curr = (t_token *)lst->data;
		/* 2-1) トークンがリダイレクト系なのに value[1] が無い → ファイル名が無い */
		if ((curr->type == TT_REDIRECT_IN || curr->type == TT_REDIRECT_OUT
				|| curr->type == TT_APPEND || curr->type == TT_HEREDOC)
			&& (!curr->value || !(curr->value[1]) || curr->value[1][0] == '\0'))
		{
			info->status = E_SYNTAX;
			return (0);
		}
		/* 2-2) 演算子同士が連続、先頭や末尾に pipe/&&/|| がある等 */
		if (prev && ((prev->type == TT_PIPE && curr->type == TT_PIPE)
				|| (prev->type == TT_AND_AND && curr->type == TT_AND_AND)
				|| (prev->type == TT_OR_OR && curr->type == TT_OR_OR)))
		{
			info->status = E_SYNTAX;
			return (0);
		}
		prev = curr;
		lst = lst->next;
	}
	return (1);
}

/*
** ------------------------------------------------------------
** 3) validate_syntax: 全体をチェック
**    - tokenize_line() 後に呼び出し、構文を最終判定する
** ------------------------------------------------------------
*/
int	validate_syntax(t_info *info)
{
	if (!info->token_list)
		return (1);
	if (!check_parentheses(info->token_list, info))
		return (0);
	if (!check_adjacency(info->token_list, info))
		return (0);
	/* 他にも必要があればチェックを追加する */
	return (1);
}
