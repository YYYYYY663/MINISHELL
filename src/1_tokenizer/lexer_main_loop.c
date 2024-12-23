/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_main_loop.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 04:58:51 by teando            #+#    #+#             */
/*   Updated: 2024/12/23 17:45:57 by teando           ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "ft_lexer.h"

int skip_spaces(const char *line, size_t *pos)
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
static t_token *create_eof_token(t_info *info)
{
	char *value;
	t_token *eof_tok;

	value = ft_strdup("");
	if (!value)
		return (NULL);
	eof_tok = create_token(TT_EOF, value, info);
	if (!eof_tok)
		free(value);
	return (eof_tok);
}

static t_token_type get_operator_token(const char *line,
									   size_t *pos, size_t *op_len)
{
	t_token_type op;

	op = get_two_char_op(&line[*pos], op_len);
	if (op != TT_ERROR)
		return (op);
	op = get_one_char_op(line[*pos]);
	if (op != TT_ERROR)
	{
		*op_len = 1;
		return (op);
	}
	return (TT_ERROR);
}

static int process_one_token(const char *line, size_t *i, t_info *info)
{
	t_token_type op_type;
	size_t op_len;
	char *value;

	skip_spaces(line, i);
	if (!line[*i])
		return (add_token(info, create_eof_token(info)));
	op_len = 0;
	op_type = get_operator_token(line, i, &op_len);
	if (op_type != TT_ERROR)
	{
		(*i) += op_len;
		value = ft_strdup("");
		if (!value)
			return (0);
		if (!add_token(info, create_token(op_type, value, info)))
		{
			free(value);
			return (0);
		}
		/* リダイレクト系なら直後にwordを取り込む => 例: > filename */
		if (op_type == TT_REDIR_IN || op_type == TT_REDIR_OUT || op_type == TT_APPEND || op_type == TT_HEREDOC)
		{
			skip_spaces(line, i);
			if (line[*i])
			{
				/* 次のwordをtokenにして、「そのtoken->value[0] = filename」 */
				if (!handle_word(line, i, info, &value))
					return (0);
				if (!add_token(info, create_token(op_type, value, info)))
					return (0);
			}
			return (1);
		}
		return (1);
	}
	if (!handle_word(line, i, info, &value))
		return (0);
	if (!add_token(info, create_token(TT_WORD, value, info)))
		return (0);
	return (1);
}

int tokenize_line(t_info *info)
{
	size_t i;
	char *line;

	line = info->source_line;
	i = 0;
	while (1)
	{
		if (!process_one_token(line, &i, info))
		{
			if (info->status == E_NONE)
				info->status = E_SYNTAX;
			return (0);
		}
		if (!line[i])
			break;
	}
	return (1);
}