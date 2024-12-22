/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 15:29:01 by teando            #+#    #+#             */
/*   Updated: 2024/12/23 05:32:05 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lexer.h"

static int	handle_word(const char *line, size_t *i, t_info *info,
		char ***cmd_argv)
{
	size_t	start;
	char	*tmp;

	start = *i;
	while (line[*i] && !ft_isspace(line[*i]) && !is_cmd_delimiter(line[*i])
		&& get_two_char_op(&line[*i], NULL) == TT_ERROR
		&& get_one_char_op(line[*i]) == TT_ERROR && get_redirect_type(&line[*i],
			NULL) == TT_ERROR)
		(*i)++;
	if ((*i - start) > 0)
	{
		tmp = ft_substr(line, start, (*i) - start);
		*cmd_argv = strs_append(*cmd_argv, tmp, info);
		free(tmp);
	}
	if (info->status != E_NONE)
		return (0);
	return (1);
}

/* ------------------ 1コマンド分解析 parse_one_command ------------------ */
int	parse_one_command(const char *line, size_t *i, t_info *info)
{
	char	**cmd_argv;
	t_list	*redir_list;

	cmd_argv = NULL;
	redir_list = NULL;
	while (1)
	{
		skip_spaces(line, i);
		if (is_cmd_delimiter(line[*i]) || get_two_char_op(&line[*i],
				NULL) != TT_ERROR || line[*i] == '\0')
			break ;
		if (get_redirect_type(&line[*i], NULL) != TT_ERROR
			&& !handle_redirect(line, i, info, &redir_list))
			return (ft_strs_clear(cmd_argv), 0);
		else if ((line[*i] == '"' || line[*i] == '\'') && !handle_quoted(line,
				i, info, &cmd_argv))
			return (0);
		else if (!handle_word(line, i, info, &cmd_argv))
			return (0);
	}
	if (cmd_argv && !add_token(info, create_token(TT_CMD, cmd_argv, info)))
		return (ft_strs_clear(cmd_argv), 0);
	if (!flush_redir_list(&redir_list, info))
		return (0);
	return (1);
}

/* ------------------ 区切り演算子トークン取得 ------------------ */
t_token	*get_operator_token(const char *line, size_t *pos, t_info *info)
{
	t_token_type	op;
	size_t			len;
	char			*op_str;
	char			**arr;

	len = 0;
	op = get_two_char_op(&line[*pos], &len);
	if (op != TT_ERROR)
	{
		op_str = ft_substr(line, *pos, len);
		(*pos) += len;
	}
	else
	{
		op = get_one_char_op(line[*pos]);
		if (op == TT_ERROR)
			return (NULL);
		len = 1;
		op_str = ft_substr(line, *pos, len);
		(*pos)++;
	}
	arr = ft_calloc(sizeof(char *), 2);
	arr[0] = op_str;
	return (create_token(op, arr, info));
}
