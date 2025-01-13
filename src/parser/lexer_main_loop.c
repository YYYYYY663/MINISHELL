/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_main_loop.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 04:58:51 by teando            #+#    #+#             */
/*   Updated: 2025/01/12 20:59:24 by teando           ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "mish_parser.h"

/**
 * @brief 2項演算子 (TT_APPEND, TT_HEREDOC) の演算子部と引数部をトークン化する
 *
 * 2項演算子 (TT_APPEND, TT_HEREDOC) の演算子部と引数部をトークン化し、
 * info->token_list に追加します。
 *
 * @param op 2項演算子のトークンタイプ (TT_APPEND, TT_HEREDOC)
 * @param line トークン化対象のソースライン
 * @param pos トークン化開始位置
 * @param info トークン化結果を保持するt_info構造体
 */
static void	handle_operator_with_arg(t_token_type op, const char *line,
		size_t *pos, t_info *info)
{
	char	*word;

	skip_spaces(line, pos);
	word = read_word(line, pos, info);
	add_token(info, create_token(op, word, info));
}

/**
 * @brief 2項演算子 (TT_APPEND, TT_HEREDOC) をトークン化する
 *
 * 2項演算子 (TT_APPEND, TT_HEREDOC) をトークン化し、
 * info->token_list に追加します。
 *
 * @param line トークン化対象のソースライン
 * @param pos トークン化開始位置
 * @param info トークン化結果を保持するt_info構造体
 *
 * @retval 1 トークン化に成功
 * @retval 0 トークン化に失敗 (TT_ERROR)
 */
static int	handle_two_char_op(const char *line, size_t *pos, t_info *info)
{
	t_token_type	op;
	size_t			len;

	op = get_two_char_op(&line[*pos], &len);
	if (op == TT_ERROR)
		return (0);
	(*pos) += len;
	if (op == TT_APPEND || op == TT_HEREDOC)
		handle_operator_with_arg(op, line, pos, info);
	else
		add_token(info, create_token(op, NULL, info));
	return (1);
}

/**
 * @brief 1項演算子をトークン化する
 *
 * 1項演算子 (TT_REDIR_IN, TT_REDIR_OUT, TT_PIPE, TT_LPAREN, TT_RPAREN,
	TT_SEMICOLON) をトークン化し、
 * info->token_list に追加します。
 *
 * @param line トークン化対象のソースライン
 * @param pos トークン化開始位置
 * @param info トークン化結果を保持するt_info構造体
 *
 * @retval 1 トークン化に成功
 * @retval 0 トークン化に失敗 (TT_ERROR)
 */
static int	handle_one_char_op(const char *line, size_t *pos, t_info *info)
{
	t_token_type	op;

	op = get_one_char_op(line[*pos]);
	if (op == TT_ERROR)
		return (0);
	(*pos)++;
	if (op == TT_REDIR_IN || op == TT_REDIR_OUT)
		handle_operator_with_arg(op, line, pos, info);
	else
		add_token(info, create_token(op, NULL, info));
	return (1);
}

/**
 * @brief 1トークンをトークン化する
 *
 * @param[in] line トークン化対象のソースライン
 * @param[in,out] pos トークン化開始位置
 * @param[in,out] info トークン化結果を保持するt_info構造体
 *
 * @retval 1 トークン化に成功
 * @retval 0 トークン化に失敗 (TT_EOF)
 * @retval -1 トークン化に失敗 (E_SYNTAX)
 *
 * 指定されたソースライン中の1トークンをトークン化し、得られたトークンを
 * info->token_listに追加します。
 *
 * トークン化に失敗した場合、info->statusにE_SYNTAXを設定します。
 */
static int	next_token(const char *line, size_t *pos, t_info *info)
{
	char	*word;

	skip_spaces(line, pos);
	if (!line[*pos])
		return (add_token(info, create_token(TT_EOF, NULL, info)), 0);
	if (handle_two_char_op(line, pos, info))
		return (1);
	if (handle_one_char_op(line, pos, info))
		return (1);
	word = read_word(line, pos, info);
	if (!word && info->status == E_SYNTAX)
		return (-1);
	add_token(info, create_token(WORD, word, info));
	return (1);
}

/**
 * @brief 1行をトークン化する
 *
 * @param[in] info トークン化結果を保持するt_info構造体
 *
 * @retval 1 トークン化に成功
 * @retval 0 トークン化に失敗
 *
 * source_lineフィールドに指定された1行をトークン化し、得られたトークンを
 * token_listフィールドに保持します。
 *
 * トークン化に失敗した場合、statusフィールドにE_SYNTAXを設定します。
 *
 * statusフィールドがE_NONEでない場合、トークン化を中断してstatusをそのまま
 * 返します。
 *
 * @details
 * - 1行をトークン化する
 * - トークン化に失敗した場合、statusフィールドにE_SYNTAXを設定する
 * - statusフィールドがE_NONEでない場合、中断してstatusをそのまま返す
 */
int	tokenize_line(t_info *info)
{
	size_t		i;
	int			ret;
	const char	*line;

	line = info->source_line;
	info->status = E_NONE;
	i = 0;
	while (1)
	{
		ret = next_token(line, &i, info);
		if (ret == 0)
			break ;
		if (ret < 0)
		{
			if (info->status == E_NONE)
				info->status = E_SYNTAX;
			return (0);
		}
	}
	return (1);
}
