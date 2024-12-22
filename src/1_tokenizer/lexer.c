/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 15:29:01 by teando            #+#    #+#             */
/*   Updated: 2024/12/23 04:18:59 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lexer.h"

/*
** ========= 5) リダイレクト(> >> < <<)解析 parse_redirect ===========
** 後続のファイル名 (空白区切り or 演算子区切り) を収集してトークンを作成
*/

static t_token	*parse_redirect(const char *line, size_t *pos, t_info *info)
{
	size_t			len;
	t_token_type	rtype;
	char			*op_str;
	size_t			start;
	char			*fname;
	char			**arr;

	len = 0;
	rtype = get_redirect_type(&line[*pos], &len);
	op_str = ft_substr(line, *pos, len);
	(*pos) += len;
	while (ft_isspace(line[*pos]))
		(*pos)++;
	start = *pos;
	while (line[*pos] && !ft_isspace(line[*pos])
		&& is_cmd_delimiter(line[*pos]) == 0 && get_two_char_op(&line[*pos],
			NULL) == TT_ERROR && get_one_char_op(line[*pos]) == TT_ERROR
		&& get_redirect_type(&line[*pos], NULL) == TT_ERROR)
	{
		(*pos)++;
	}
	fname = ft_substr(line, start, (*pos) - start);
	arr = NULL;
	arr = strs_append(arr, op_str, info);
	if (fname && *fname != '\0')
		arr = strs_append(arr, fname, info);
	free(op_str);
	free(fname);
	return (create_token(rtype, arr, info));
}

/*
** ========= 6) 1コマンド文を解析する parse_one_command ===========
** コマンド本体 + クォート内文字列 + リダイレクト をまとめる。
*/

static int	parse_one_command(const char *line, size_t *i, t_info *info)
{
	char	**cmd_argv;
	t_list	*redir_list;
	t_token	*redir_tok;
	char	*quoted;
	size_t	start;

	cmd_argv = NULL;
	redir_list = NULL;
	while (1)
	{
		while (ft_isspace(line[*i]))
			(*i)++;
		if (is_cmd_delimiter(line[*i]) || get_two_char_op(&line[*i],
				NULL) != TT_ERROR || line[*i] == '\0')
			break ;
		if (get_redirect_type(&line[*i], NULL) != TT_ERROR)
		{
			redir_tok = parse_redirect(line, i, info);
			if (!redir_tok)
				return (ft_strs_clear(cmd_argv), 0);
			ft_lstadd_back(&redir_list, ft_lstnew(redir_tok));
			continue ;
		}
		if (line[*i] == '"' || line[*i] == '\'')
		{
			quoted = read_quoted(line, i, info);
			if (!quoted)
				return (ft_strs_clear(cmd_argv), 0);
			cmd_argv = strs_append(cmd_argv, quoted, info);
			free(quoted);
		}
		else
		{
			start = *i;
			while (line[*i] && !ft_isspace(line[*i])
				&& is_cmd_delimiter(line[*i]) == 0 && get_two_char_op(&line[*i],
					NULL) == TT_ERROR && get_one_char_op(line[*i]) == TT_ERROR
				&& get_redirect_type(&line[*i], NULL) == TT_ERROR)
				(*i)++;
			if ((*i - start) > 0)
				cmd_argv = strs_append(cmd_argv, ft_substr(line, start, (*i)
							- start), info);
		}
		if (info->status != E_NONE)
			return (ft_strs_clear(cmd_argv), 0);
	}
	if (cmd_argv)
	{
		if (!add_token(info, create_token(TT_CMD, cmd_argv, info)))
			return (ft_strs_clear(cmd_argv), 0);
	}
	while (redir_list)
	{
		redir_tok = (t_token *)redir_list->data;
		if (!add_token(info, redir_tok))
			return (0);
		ft_lstdel_front(&redir_list, NULL);
	}
	return (1);
}

/*
** ========= 7) 区切り演算子トークン ( | ; && || ... ) 取得 get_operator_token
*/

static t_token	*get_operator_token(const char *line, size_t *pos, t_info *info)
{
	t_token_type	op;
	char			*op_str;
	char			**arr;
	size_t			len;

	len = 0;
	op = get_two_char_op(&line[*pos], &len);
	if (op != TT_ERROR)
	{
		op_str = ft_substr(line, *pos, len);
		(*pos) += len;
		arr = xmalloc(sizeof(char *) * 2, info);
		if (!arr)
			return (NULL);
		arr[0] = op_str;
		arr[1] = NULL;
		return (create_token(op, arr, info));
	}
	op = get_one_char_op(line[*pos]);
	if (op != TT_ERROR)
	{
		len = 1;
		op_str = ft_substr(line, *pos, len);
		(*pos)++;
		arr = xmalloc(sizeof(char *) * 2, info);
		if (!arr)
			return (NULL);
		arr[0] = op_str;
		arr[1] = NULL;
		return (create_token(op, arr, info));
	}
	return (NULL);
}

/*
** ========= 8) tokenize_line: 全体のメインループ ===========
**  1) 1コマンドを parse_one_command
**  2) 区切り演算子(|, &&, ||, ;, ...) をトークン追加
**  3) 最後に EOFトークンを付与
*/

static int	tokenize_line(t_info *info)
{
	size_t		i;
	const char	*line;
	t_token		*op_tok;
	char		**arr;
	t_token		*eof_tok;

	line = info->source_line;
	i = 0;
	while (1)
	{
		while (ft_isspace(line[i]))
			i++;
		if (!parse_one_command(line, &i, info))
		{
			if (info->status == E_NONE)
				info->status = E_SYNTAX;
			return (0);
		}
		if (info->status != E_NONE)
			return (0);
		if (line[i] == '\0')
			break ;
		op_tok = get_operator_token(line, &i, info);
		if (op_tok && !add_token(info, op_tok))
			return (0);
		if (line[i] == '\0')
			break ;
	}
	arr = (char **)xmalloc(sizeof(char *) * 2, info);
	if (!arr)
		return (0);
	arr[0] = ft_strdup("EOF");
	arr[1] = NULL;
	eof_tok = create_token(TT_EOF, arr, info);
	if (!eof_tok || !add_token(info, eof_tok))
		return (0);
	return (1);
}
