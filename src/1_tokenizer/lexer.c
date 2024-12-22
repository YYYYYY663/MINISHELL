/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 15:29:01 by teando            #+#    #+#             */
/*   Updated: 2024/12/23 04:52:21 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lexer.h"

/* ------------------ read_quoted ------------------ */
/* Extract contents between matching quote chars.    */
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

/* line[*pos] からファイル名となりうる文字列を取得 */
static char	*read_filename(const char *line, size_t *pos)
{
	size_t	start;
	char	*fname;

	start = *pos;
	while (line[*pos] && !ft_isspace(line[*pos])
		&& !is_cmd_delimiter(line[*pos]) && get_two_char_op(&line[*pos],
			NULL) == TT_ERROR && get_one_char_op(line[*pos]) == TT_ERROR
		&& get_redirect_type(&line[*pos], NULL) == TT_ERROR)
		(*pos)++;
	fname = ft_substr(line, start, (*pos) - start);
	return (fname);
}

/* ------------------ リダイレクト解析 parse_redirect ------------------ */
static t_token	*parse_redirect(const char *line, size_t *pos, t_info *info)
{
	t_token_type	rtype;
	size_t			len;
	char			*op_str;
	char			*fname;
	char			**arr;

	len = 0;
	rtype = get_redirect_type(&line[*pos], &len);
	op_str = ft_substr(line, *pos, len);
	(*pos) += len;
	skip_spaces(line, pos);
	fname = read_filename(line, pos);
	arr = NULL;
	arr = strs_append(arr, op_str, info);
	if (fname && *fname != '\0')
		arr = strs_append(arr, fname, info);
	free(op_str);
	free(fname);
	return (create_token(rtype, arr, info));
}

/* ------------------ parse_one_command のヘルパー ------------------ */

static int	handle_redirect(const char *line, size_t *i, t_info *info,
		t_list **redir_list)
{
	t_token	*redir_tok;

	redir_tok = parse_redirect(line, i, info);
	if (!redir_tok)
		return (0);
	ft_lstadd_back(redir_list, ft_lstnew(redir_tok));
	return (1);
}

static int	handle_quoted(const char *line, size_t *i, t_info *info,
		char ***cmd_argv)
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

/* ------------------ リダイレクトのフラッシュ処理 ------------------ */
static int	flush_redir_list(t_list **redir_list, t_info *info)
{
	t_list	*next;
	t_token	*tok;

	while (*redir_list)
	{
		next = (*redir_list)->next;
		tok = (t_token *)(*redir_list)->data;
		if (!add_token(info, tok))
			return (ft_lstdel_front(redir_list, NULL), 0);
		ft_lstdel_front(redir_list, NULL);
		*redir_list = next;
	}
	return (1);
}

/* ------------------ 1コマンド分解析 parse_one_command ------------------ */
static int	parse_one_command(const char *line, size_t *i, t_info *info)
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
static t_token	*get_operator_token(const char *line, size_t *pos, t_info *info)
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

/* ------------------ tokenize_line: 全体メインループ ------------------ */

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
