/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_ops.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 04:08:08 by teando            #+#    #+#             */
/*   Updated: 2024/12/23 04:13:58 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lexer.h"

/*
** ========= Command判定ヘルパー ===========
** is_cmd_delimiter, read_quoted
*/

/* --- 行末, パイプ, 括弧, セミコロンなどをコマンド区切りとする --- */
int	is_cmd_delimiter(char c)
{
	if (c == '\0')
		return (1);
	if (c == '|' || c == ';' || c == '(' || c == ')')
		return (1);
	return (0);
}

/* --- クォートで囲まれた文字列を取り出す --- */
char	*read_quoted(const char *line, size_t *pos, t_info *info)
{
	char	quote;
	size_t	start;
	char	*content;

	quote = line[*pos];
	start = *pos + 1;
	(*pos)++;
	while (line[*pos] && line[*pos] != quote)
		(*pos)++;
	if (!line[*pos])
	{
		info->status = E_SYNTAX;
		return (NULL);
	}
	content = ft_substr(line, start, (*pos) - start);
	(*pos)++;
	return (content);
}

/*
** ========= 演算子チェック:リダイレクト, 1文字/2文字演算子 ===========
** get_redirect_type, get_two_char_op, get_one_char_op
*/

t_token_type	get_redirect_type(const char *s, size_t *len)
{
	if (ft_strncmp(s, ">>", 2) == 0 && len)
	{
		*len = 2;
		return (TT_APPEND);
	}
	if (ft_strncmp(s, "<<", 2) == 0 && len)
	{
		*len = 2;
		return (TT_HEREDOC);
	}
	if (*s == '>')
	{
		if (len)
			*len = 1;
		return (TT_REDIRECT_OUT);
	}
	if (*s == '<')
	{
		if (len)
			*len = 1;
		return (TT_REDIRECT_IN);
	}
	return (TT_ERROR);
}

t_token_type	get_two_char_op(const char *s, size_t *len)
{
	if (ft_strncmp(s, "&&", 2) == 0 && len)
	{
		*len = 2;
		return (TT_AND_AND);
	}
	if (ft_strncmp(s, "||", 2) == 0 && len)
	{
		*len = 2;
		return (TT_OR_OR);
	}
	return (TT_ERROR);
}

t_token_type	get_one_char_op(char c)
{
	if (c == '|')
		return (TT_PIPE);
	if (c == '(')
		return (TT_LPAREN);
	if (c == ')')
		return (TT_RPAREN);
	if (c == ';')
		return (TT_SEMICOLON);
	return (TT_ERROR);
}
