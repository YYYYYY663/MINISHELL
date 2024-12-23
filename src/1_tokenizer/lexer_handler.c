/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 14:07:53 by teando            #+#    #+#             */
/*   Updated: 2024/12/25 09:52:00 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lexer.h"

void	skip_spaces(const char *line, size_t *pos)
{
	while (line[*pos] && ft_isspace(line[*pos]))
		(*pos)++;
}

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

char	*read_word(const char *line, size_t *pos, t_info *info)
{
	size_t	start;
	char	*res;

	if (line[*pos] == '\'' || line[*pos] == '"')
		return (read_quoted_word(line, pos, info));
	start = *pos;
	while (line[*pos])
	{
		if (ft_isspace(line[*pos]) || get_two_char_op(&line[*pos], NULL) != TT_ERROR
			|| get_one_char_op(line[*pos]) != TT_ERROR)
			break ;
		(*pos)++;
	}
	res = ft_substr(line, start, (*pos - start));
	return (res);
}
