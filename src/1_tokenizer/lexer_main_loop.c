/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_main_loop.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 04:58:51 by teando            #+#    #+#             */
/*   Updated: 2024/12/23 19:05:53 by teando           ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "ft_lexer.h"

static void handle_operator_with_arg(t_token_type op, const char *line,
									 size_t *pos, t_info *info)
{
	char *word;

	skip_spaces(line, pos);
	word = read_word(line, pos, info);
	add_token(info, create_token(op, word, info));
}

static int handle_two_char_op(const char *line, size_t *pos, t_info *info)
{
	t_token_type op;
	size_t len;

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

static int handle_one_char_op(const char *line, size_t *pos, t_info *info)
{
	t_token_type op;

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

static int next_token(const char *line, size_t *pos, t_info *info)
{
	char *word;

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
	add_token(info, create_token(TT_WORD, word, info));
	return (1);
}

int tokenize_line(t_info *info)
{
	size_t i;
	int ret;
	const char *line;

	line = info->source_line;
	info->status = E_NONE;
	i = 0;
	while (1)
	{
		ret = next_token(line, &i, info);
		if (ret == 0)
			break;
		if (ret < 0)
		{
			if (info->status == E_NONE)
				info->status = E_SYNTAX;
			return (0);
		}
	}
	return (1);
}
