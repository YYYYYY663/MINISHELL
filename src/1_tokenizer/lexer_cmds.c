/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_cmds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 15:29:01 by teando            #+#    #+#             */
/*   Updated: 2024/12/25 09:57:00 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lexer.h"

int	next_token(const char *line, size_t *pos, t_info *info)
{
	t_token_type	op;
	size_t			len;
	char			*word;

	skip_spaces(line, pos);
	if (!line[*pos])
	{
		add_token(info, create_token(TT_EOF, NULL, info));
		return (0);
	}
	op = get_two_char_op(&line[*pos], &len);
	if (op != TT_ERROR)
	{
		(*pos) += len;
		if (op == TT_APPEND || op == TT_HEREDOC)
		{
			skip_spaces(line, pos);
			word = read_word(line, pos, info);
			add_token(info, create_token(op, word, info));
		}
		else
			add_token(info, create_token(op, NULL, info));
		return (1);
	}
	op = get_one_char_op(line[*pos]);
	if (op != TT_ERROR)
	{
		(*pos)++;
		if (op == TT_REDIR_IN || op == TT_REDIR_OUT)
		{
			skip_spaces(line, pos);
			word = read_word(line, pos, info);
			add_token(info, create_token(op, word, info));
		}
		else
			add_token(info, create_token(op, NULL, info));
		return (1);
	}
	word = read_word(line, pos, info);
	if (!word && info->status == E_SYNTAX)
		return (-1);
	add_token(info, create_token(TT_WORD, word, info));
	return (1);
}
