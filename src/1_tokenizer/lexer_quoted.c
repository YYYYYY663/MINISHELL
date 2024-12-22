/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_quoted.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 05:13:53 by teando            #+#    #+#             */
/*   Updated: 2024/12/23 05:35:36 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lexer.h"

/* ------------------ read_quoted ------------------ */
/* Extract contents between matching quote chars.    */
static char	*read_quoted(const char *line, size_t *pos, t_info *info)
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

int	handle_quoted(const char *line, size_t *i, t_info *info, char ***cmd_argv)
{
	char	*quoted;

	quoted = read_quoted(line, i, info);
	if (!quoted)
	{
		ft_strs_clear(*cmd_argv);
		return (0);
	}
	*cmd_argv = strs_append(*cmd_argv, quoted, info);
	free(quoted);
	return (1);
}
