/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_syntax.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 14:02:42 by teando            #+#    #+#             */
/*   Updated: 2024/12/23 16:21:51 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lexer.h"

/*
** check_parentheses_stack:
**   スタックを使って '(' と ')' の整合性を確認する。
**   - '(' が閉じられない
**   - ')' が先に来てしまう
**   - () の中身が完全に空 (必要に応じてチェック)
*/
// static int	check_parentheses_stack(t_list *lst, t_info *info)
// {
// 	char	stack[256];
// 	int		top;
// 	t_token	*tok;
// 	int		i;

// 	int last_lparen_index; // '(' 直後に何も無いかを調べる例
// 	top = -1;
// 	last_lparen_index = -1;
// 	i = 0;
// 	while (lst)
// 	{
// 		tok = (t_token *)lst->data;
// 		if (tok->type == TT_LPAREN)
// 		{
// 			if (top < 255)
// 			{
// 				stack[++top] = '(';
// 				last_lparen_index = i; // '(' が出現したリスト上のインデックスを記録
// 			}
// 			else
// 			{
// 				// スタックオーバーフロー(極端に多い括弧)
// 				info->status = E_SYNTAX;
// 				return (0);
// 			}
// 		}
// 		else if (tok->type == TT_RPAREN)
// 		{
// 			// '(' がないのに ')' が来た
// 			if (top < 0)
// 			{
// 				info->status = E_SYNTAX;
// 				return (0);
// 			}
// 			top--;
// 			/* 空括弧チェック (optional):
// 				* もし '(' 直後がすぐ ')' で、その間にコマンド等トークンがなければエラーにしたい場合
// 				* 例: () → エラー
// 				*/
// 			if (i == last_lparen_index + 1)
// 			{
// 				// ( ) 直後 => 中身空 → エラー
// 				info->status = E_SYNTAX;
// 				return (0);
// 			}
// 		}
// 		lst = lst->next;
// 		i++;
// 	}
// 	// '(' が余っている
// 	if (top != -1)
// 	{
// 		info->status = E_SYNTAX;
// 		return (0);
// 	}
// 	return (1);
// }

/*
** is_operator_token:
**   パイプや&&, ||, ;, 括弧など「演算子扱い」にするトークンを判定。
**   - ここでは CMD/REDIRECT 等は false。
**   - () は演算子というよりはグルーピングトークンだが、
**     「コマンドが無いのに演算子が並んでる」等のチェックに含めたい場合はtrueにしてもOK。
*/
static int	is_operator_token(t_token_type ttype)
{
	if (ttype == TT_PIPE || ttype == TT_AND_AND || ttype == TT_OR_OR
		|| ttype == TT_SEMICOLON || ttype == TT_LPAREN || ttype == TT_RPAREN)
		return (1);
	return (0);
}

/*
** check_operator_positions:
**   - 先頭や末尾が不正トークン (例: `|`, `&&`, `;`, `(` が末尾 etc)
**   - 演算子が連続してしまうケース
**   - `||` はトークンとしてはOKだが、同様に先頭/末尾にあるときはエラー
**   - セミコロンの連続 `;;` など
*/
static int	check_operator_positions(t_list *lst, t_info *info)
{
	t_token	*prev_tok;
	t_token	*curr_tok;
	t_list	*head;
	int		index;

	prev_tok = NULL;
	head = lst;
	index = 0;
	// 空なら何もしない(source_line = ""など) → シェル的には何も実行しないだけ
	if (!head)
		return (1);
	while (head)
	{
		curr_tok = (t_token *)head->data;
		// unknown token (TT_ERROR) が混入していれば構文エラーにする
		if (curr_tok->type == TT_ERROR)
		{
			info->status = E_SYNTAX;
			return (0);
		}
		// 先頭で不正トークンかどうか
		if (index == 0)
		{
			// 先頭にこれらがあるとエラー
			if (curr_tok->type == TT_PIPE || curr_tok->type == TT_AND_AND
				|| curr_tok->type == TT_SEMICOLON
				|| curr_tok->type == TT_RPAREN)
			{
				info->status = E_SYNTAX;
				return (0);
			}
		}
		// 末尾で不正トークンかどうか (次が無いのに演算子だけで終わる など)
		if (!head->next)
		{
			// 例えば末尾が `|`, `&&`, `(` の場合はエラー
			if (curr_tok->type == TT_PIPE || curr_tok->type == TT_AND_AND
				|| curr_tok->type == TT_LPAREN)
			{
				info->status = E_SYNTAX;
				return (0);
			}
		}
		// 演算子の連続チェック
		if (prev_tok && is_operator_token(prev_tok->type)
			&& is_operator_token(curr_tok->type))
		{
			/*
			** 例:  ';;' or '| |' or '&& &&' など
			** ただし '&& ||' のように別演算子の並びもNG とするかは要件次第
			** ここでは一律「演算子同士が連続」でエラーにしている。
			*/
			info->status = E_SYNTAX;
			return (0);
		}
		// セミコロンの連続 ;; だけを個別に見たい場合:
		if (prev_tok && prev_tok->type == TT_SEMICOLON
			&& curr_tok->type == TT_SEMICOLON)
		{
			// ;; は構文エラー
			info->status = E_SYNTAX;
			return (0);
		}
		prev_tok = curr_tok;
		head = head->next;
		index++;
	}
	return (1);
}

/*
** check_redirect_rules:
**   リダイレクト演算子(>, >>, <, <<) の後に「ファイル名がない/おかしなトークンが続く」等を検出
**   - 例: echo > | cat    → '>' の直後が '|' なのでNG
**   - 例: echo >>         → ファイル名不在
**   - 例: cat << &&       → '<<' の直後が '&&' なのでNG
*/
static int	check_redirect_rules(t_list *lst, t_info *info)
{
	t_token	*curr;
	t_list	*node;
	char	**redirect_value;

	node = lst;
	while (node)
	{
		curr = (t_token *)node->data;
		if (curr->type == TT_REDIRECT_IN || curr->type == TT_REDIRECT_OUT
			|| curr->type == TT_APPEND || curr->type == TT_HEREDOC)
		{
			redirect_value = (char **)curr->value;
			if (!redirect_value[0] || !redirect_value[1])
			{
				info->status = E_SYNTAX;
				return (0);
			}
		}
		node = node->next;
	}
	return (1);
}

/*
** check_empty_command:
**   オペレータ同士に挟まれていないか等、実際に "コマンドやリダイレクト" が無い区間があるかを簡易確認する。
**   - 例: echo && && echo   → 中間が空コマンド
**   - 例: ; ;   → 連続セミコロン (上のoperator checkでも弾くが)
**
** シンプルには "CMD またはリダイレクト系 の間に何もなく演算子が続いたら空" とみなしてエラー。
** ここでは例示的に、もっと簡易な判定で済ませています。
*/
static int	check_empty_command(t_list *lst, t_info *info)
{
	t_token_type	prev_type;
	t_token_type	curr_type;
	t_list			*node;

	prev_type = TT_ERROR;
	node = lst;
	while (node)
	{
		curr_type = ((t_token *)node->data)->type;
		/*
		** 演算子 → 演算子 の間にCMD/リダイレクトが無ければ空コマンド
		** ただし '&&', '||', '|' など全て "オペレータ" として判定
		*/
		if (is_operator_token(prev_type) && is_operator_token(curr_type))
		{
			// 直前直後がどちらもオペレータ → その間にコマンドなし
			info->status = E_SYNTAX;
			return (0);
		}
		prev_type = curr_type;
		node = node->next;
	}
	return (1);
}
/*
** ------------------------------------------------------------
** validate_syntax: 全体をチェック
**    - tokenize_line() 後に呼び出し、構文を最終判定する
** ------------------------------------------------------------
*/
int	validate_syntax(t_info *info)
{
	if (!info->token_list)
		return (0);
	/* 1) 括弧の対応チェック */
	// if (!check_parentheses_stack(info->token_list, info))
	// 	return (0);
	/* 2) 演算子位置/連続チェック */
	if (!check_operator_positions(info->token_list, info))
		return (0);
	/* 3) リダイレクト後のファイル名などのチェック */
	if (!check_redirect_rules(info->token_list, info))
		return (0);
	/* 4) 空コマンド(演算子だけ)チェック */
	if (!check_empty_command(info->token_list, info))
		return (0);
	return (1);
}
