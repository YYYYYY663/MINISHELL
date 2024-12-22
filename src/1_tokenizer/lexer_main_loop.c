/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_main_loop.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 04:58:51 by teando            #+#    #+#             */
/*   Updated: 2024/12/23 05:43:19 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lexer.h"

/* ------------------ tokenize_line: 全体メインループ ------------------ */

int	skip_spaces(const char *line, size_t *pos)
{
	while (ft_isspace(line[*pos]))
		(*pos)++;
	return (1);
}

static int	process_operator(const char *line, size_t *i, t_info *info)
{
	t_token	*op_tok;

	op_tok = get_operator_token(line, i, info);
	if (op_tok && !add_token(info, op_tok))
		return (0);
	return (1);
}

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

int	tokenize_line(t_info *info)
{
	size_t		i;
	const char	*line;

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
		if (!process_operator(line, &i, info))
			return (0);
		if (line[i] == '\0')
			break ;
	}
	return (add_eof_token(info));
}
