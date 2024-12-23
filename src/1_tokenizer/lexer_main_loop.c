/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_main_loop.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 04:58:51 by teando            #+#    #+#             */
/*   Updated: 2024/12/23 14:27:31 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lexer.h"

/*
** ========= スペースをスキップ skip_spaces ===========
**
**   line: 1行の文字列
**   pos: 現在の文字位置
**
**   line内の現在位置から連続するスペースをスキップし、
**   posを次の非スペース文字の位置に更新します。
**   常に1を返します。
*/
int	skip_spaces(const char *line, size_t *pos)
{
	while (ft_isspace(line[*pos]))
		(*pos)++;
	return (1);
}

/*
** ========= EOFトークンを作成しtoken_listに追加 add_eof_token ===========
**
**   info: システム情報
**
**   EOFトークンを作成し、それをトークンリストに追加する。
**   メモリ割り当てに失敗した場合やトークン追加に失敗した場合は0を返す。
**   成功した場合は1を返す。
*/
static int	add_eof_token(t_info *info)
{
	char	**arr;
	t_token	*eof_tok;

	arr = ft_calloc(sizeof(char *), 2);
	if (!arr)
		return (0);
	arr[0] = ft_strdup("EOF");
	eof_tok = create_token(TT_EOF, arr, info);
	if (!eof_tok || !add_token(info, eof_tok))
		return (0);
	return (1);
}

/*
** ========= tokenize_line: 1行をトークン化 ===========
**
**   info: system_info
**
**   1行をトークン化し、token_listに追加する。
**   syntax errorが起きた場合はinfo->statusにE_SYNTAXを設定し、0を返す。
**   それ以外は、1を返す。
*/
int	tokenize_line(t_info *info)
{
	size_t		i;
	const char	*line;
	t_token		*op_tok;

	line = info->source_line;
	i = 0;
	while (1)
	{
		skip_spaces(line, &i);
		if (!parse_one_command(line, &i, info))
		{
			if (info->status == E_NONE)
				info->status = E_SYNTAX;
			return (0);
		}
		op_tok = get_operator_token(line, &i, info);
		if (op_tok && !add_token(info, op_tok))
			return (0);
		if (line[i] == '\0')
			break ;
	}
	return (add_eof_token(info));
}
