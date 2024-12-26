/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 04:10:42 by teando            #+#    #+#             */
/*   Updated: 2024/12/23 20:26:26 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lexer.h"

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
	#ifdef FUNC_OUT
		printf("%s\n",__func__);
	#endif

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

const char	*type_to_str(t_token_type t)
{
	if (t == TT_WORD)
		return ("TT_WORD");
	if (t == TT_PIPE)
		return ("TT_PIPE");
	if (t == TT_REDIR_IN)
		return ("TT_REDIR_IN");
	if (t == TT_APPEND)
		return ("TT_APPEND");
	if (t == TT_REDIR_OUT)
		return ("TT_REDIR_OUT");
	if (t == TT_HEREDOC)
		return ("TT_HEREDOC");
	if (t == TT_LPAREN)
		return ("TT_LPAREN");
	if (t == TT_RPAREN)
		return ("TT_RPAREN");
	if (t == TT_AND_AND)
		return ("TT_AND_AND");
	if (t == TT_OR_OR)
		return ("TT_OR_OR");
	if (t == TT_SEMICOLON)
		return ("TT_SEMICOLON");
	if (t == TT_EOF)
		return ("TT_EOF");
	return ("TT_ERROR");
}

void	debug_print_token_list(t_list *list)
{
	t_token	*tok;

	while (list)
	{
		tok = (t_token *)list->data;
		ft_printf("type: %s, value: ", type_to_str(tok->type));
		if (tok->value)
			ft_printf("[%s]\n", tok->value);
		else
			ft_printf("NULL\n");
		list = list->next;
	}
}
