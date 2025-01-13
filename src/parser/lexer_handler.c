/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymizukam <ymizukam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 14:07:53 by teando            #+#    #+#             */
/*   Updated: 2025/01/12 21:35:30 by ymizukam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mish_parser.h"

t_token_type	get_two_char_op(const char *s, size_t *len)
{
	if (!s || !s[0] || !s[1])
		return (TT_ERROR);
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
	if (c == '>')
		return (TT_REDIR_OUT);
	if (c == '<')
		return (TT_REDIR_IN);
	if (c == '|')
		return (PIPE);
	if (c == '(')
		return (TT_LPAREN);
	if (c == ')')
		return (TT_RPAREN);
	if (c == ';')
		return (TT_SEMICOLON);
	return (TT_ERROR);
}

void	skip_spaces(const char *line, size_t *pos)
{
	while (line[*pos] && ft_isspace(line[*pos]))
		(*pos)++;
}

/**
 * read_quoted_word:
 *  line[pos]から始まる文字列をreadし、line[pos] = quote,  line[pos + 1]
	- line[pos] = len という文字列を抽出して返す
 *  その後、line[pos]をlenぶん進める
 *  例えばline[pos] = ' " 'の場合、line[pos] = " " という文字列を抽出して返し、line[pos]を進める
 *  quoteがなくてEOFに達した場合はinfo->status = E_SYNTAXを設定してNULLを返す
 *  malloc failedの場合はinfo->status = E_MALLOCを設定してNULLを返す
 *  @param line:  line[pos]から始まる文字列
 *  @param pos:   line[pos]を示すポインタ
 *  @param info:  statusを保持する構造体
 *  @return:      抽出された文字列
 */
static char	*read_quoted_word(const char *line, size_t *pos, t_info *info)
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
	content = ft_substr(line, start, (*pos - start));
	(*pos)++;
	return (content);
}

/**
 * read_word:
 *  line[pos]から始まる文字列をreadし、line[pos]がspace, 2文字演算子, 1文字演算子のいずれかになるまで進める
 *  その後、line[start] - line[pos]という文字列を抽出して返す
 *  line[pos]がそのままEOFに達した場合はinfo->status = E_SYNTAXを設定してNULLを返す
 *  malloc failedの場合はinfo->status = E_MALLOCを設定してNULLを返す
 *  @param line:  line[pos]から始まる文字列
 *  @param pos:   line[pos]を示すポインタ
 *  @param info:  statusを保持する構造体
 *  @return:      抽出された文字列
 */
char	*read_word(const char *line, size_t *pos, t_info *info)
{
	size_t	start;
	char	*res;

	if (line[*pos] == '\'' || line[*pos] == '"')
		return (read_quoted_word(line, pos, info));
	start = *pos;
	while (line[*pos])
	{
		if (ft_isspace(line[*pos]) || get_two_char_op(&line[*pos],
				NULL) != TT_ERROR || get_one_char_op(line[*pos]) != TT_ERROR)
			break ;
		(*pos)++;
	}
	res = ft_substr(line, start, (*pos - start));
	return (res);
}
