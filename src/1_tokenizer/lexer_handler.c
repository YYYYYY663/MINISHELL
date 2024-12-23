/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 14:07:53 by teando            #+#    #+#             */
/*   Updated: 2024/12/23 19:10:23 by teando           ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "ft_lexer.h"

t_token_type get_two_char_op(const char *s, size_t *len)
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

t_token_type get_one_char_op(char c)
{
	if (c == '>')
		return (TT_REDIR_OUT);
	if (c == '<')
		return (TT_REDIR_IN);
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

void skip_spaces(const char *line, size_t *pos)
{
	while (line[*pos] && ft_isspace(line[*pos]))
		(*pos)++;
}

static char *read_quoted_word(const char *line, size_t *pos, t_info *info)
{
	char quote;
	size_t start;
	char *content;

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

char *read_word(const char *line, size_t *pos, t_info *info)
{
	size_t start;
	char *res;

	if (line[*pos] == '\'' || line[*pos] == '"')
		return (read_quoted_word(line, pos, info));
	start = *pos;
	while (line[*pos])
	{
		if (ft_isspace(line[*pos]) || get_two_char_op(&line[*pos], NULL) != TT_ERROR || get_one_char_op(line[*pos]) != TT_ERROR)
			break;
		(*pos)++;
	}
	res = ft_substr(line, start, (*pos - start));
	return (res);
}
