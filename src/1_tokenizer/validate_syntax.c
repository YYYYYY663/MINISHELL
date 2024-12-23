/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_syntax.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 14:02:42 by teando            #+#    #+#             */
/*   Updated: 2024/12/23 18:42:29 by teando           ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "ft_lexer.h"

/*
** is_operator_token:
**   パイプや&&, ||, ;, 括弧など「演算子扱い」にするトークンを判定。
**   - ここでは CMD/REDIRECT 等は false。
**   - () は演算子というよりはグルーピングトークンだが、
**     「コマンドが無いのに演算子が並んでる」等のチェックに含めたい場合はtrueにしてもOK。
*/
int is_operator_token(t_token_type ttype)
{
	if (ttype == TT_PIPE || ttype == TT_AND_AND || ttype == TT_OR_OR || ttype == TT_SEMICOLON || ttype == TT_LPAREN || ttype == TT_RPAREN)
		return (1);
	return (0);
}

/*
** ------------------------------------------------------------
** validate_syntax: 全体をチェック
**    - tokenize_line() 後に呼び出し、構文を最終判定する
** ------------------------------------------------------------
*/

static int check_error_token(t_token *curr, t_info *info)
{
	if (curr->type == TT_ERROR)
	{
		info->status = E_SYNTAX;
		return (0);
	}
	return (1);
}

static int check_redirect_token(t_token *curr, t_info *info)
{
	if ((curr->type == TT_REDIR_IN || curr->type == TT_APPEND || curr->type == TT_REDIR_OUT || curr->type == TT_HEREDOC) && (!curr->value || curr->value[0] == '\0'))
	{
		info->status = E_SYNTAX;
		return (0);
	}
	return (1);
}

// static int check_consecutive_tokens(t_token *prev, t_token *curr, t_info *info)
// {
// 	if (prev && (prev->type != TT_WORD && prev->type != TT_EOF && curr->type != TT_WORD && curr->type != TT_EOF && curr->type != TT_REDIR_IN && curr->type != TT_REDIR_OUT && curr->type != TT_APPEND && curr->type != TT_HEREDOC))
// 	{
// 		info->status = E_SYNTAX;
// 		return (0);
// 	}
// 	return (1);
// }

int validate_syntax(t_info *info)
{
	t_list *node;
	// t_token *prev;
	t_token *curr;

	node = info->token_list;
	if (!node)
		return (1);
	// prev = NULL;
	while (node)
	{
		curr = (t_token *)node->data;
		if (!check_error_token(curr, info))
			return (0);
		if (!check_redirect_token(curr, info))
			return (0);
		// if (!check_consecutive_tokens(prev, curr, info))
		// 	return (0);
		// prev = curr;
		node = node->next;
	}
	return (1);
}
