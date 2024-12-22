/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 15:29:01 by teando            #+#    #+#             */
/*   Updated: 2024/12/23 04:04:57 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lexer.h"

/************************************
 * 文字列配列操作のヘルパー
 ************************************/
/* --- 文字列配列の末尾に一要素追加した新配列を返す --- */
/* 要素数カウント -> 再alloc -> 代入 */
static char	**strs_append(char **src, const char *newstr, t_info *info)
{
	int		i;
	char	**dst;

	if (!newstr)
		return (src);
	i = 0;
	while (src && src[i])
		i++;
	dst = xmalloc(sizeof(char *) * (i + 2), info);
	if (!dst)
	{
		ft_strs_clear(src);
		return (NULL);
	}
	i = 0;
	while (src && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = ft_strdup(newstr);
	dst[i + 1] = NULL;
	free(src);
	return (dst);
}

/*
** ========= 2) トークン生成系 ===========
** create_token, add_token
*/

/* --- t_token を新規作成 --- */
static t_token	*create_token(t_token_type type, char **value, t_info *info)
{
	t_token	*tok;

	tok = (t_token *)xmalloc(sizeof(t_token), info);
	if (!tok)
	{
		ft_strs_clear(value);
		return (NULL);
	}
	tok->type = type;
	tok->value = value;
	return (tok);
}

/* --- t_list (info->token_list) にトークンを追加 --- */
static int	add_token(t_info *info, t_token *tok)
{
	t_list	*node;
	t_list	*tmp;

	if (!tok)
		return (0);
	node = (t_list *)xmalloc(sizeof(t_list), info);
	if (!node)
	{
		ft_strs_clear(tok->value);
		free(tok);
		return (0);
	}
	node->data = tok;
	node->next = NULL;
	if (!info->token_list)
		info->token_list = node;
	else
	{
		tmp = info->token_list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = node;
	}
	return (1);
}

/*
** ========= 3) 演算子チェック:リダイレクト, 1文字/2文字演算子 ===========
** get_redirect_type, get_two_char_op, get_one_char_op
*/

static t_token_type	get_redirect_type(const char *s, size_t *len)
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

static t_token_type	get_two_char_op(const char *s, size_t *len)
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

static t_token_type	get_one_char_op(char c)
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

/*
** ========= 4) 判定ヘルパー ===========
** is_cmd_delimiter, read_quoted
*/

/* --- 行末, パイプ, 括弧, セミコロンなどをコマンド区切りとする --- */
static int	is_cmd_delimiter(char c)
{
	if (c == '\0')
		return (1);
	if (c == '|' || c == ';' || c == '(' || c == ')')
		return (1);
	return (0);
}

/* --- クォートで囲まれた文字列を取り出す --- */
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

/*
** ========= 9) 外部公開関数 ===========
	xlexer,
	token_list_free,
	debug_print_token_list
*/

t_status	xlexer(t_info *info)
{
	info->token_list = NULL;
	info->status = E_NONE;
	if (!info->source_line)
		return (info->status);
	if (!tokenize_line(info) && info->status == E_NONE)
		info->status = E_SYNTAX;
	return (info->status);
}

void	token_list_free(t_list **token_list)
{
	t_list	*cur;
	t_list	*nx;
	t_token	*tok;

	cur = *token_list;
	while (cur)
	{
		nx = cur->next;
		tok = (t_token *)cur->data;
		if (tok)
		{
			ft_strs_clear(tok->value);
			free(tok);
		}
		free(cur);
		cur = nx;
	}
	*token_list = NULL;
}

void	debug_print_token_list(t_list *list)
{
	t_token	*tok;

	while (list)
	{
		tok = (t_token *)list->data;
		ft_printf("type: %d, value: ", tok->type);
		if (tok->value)
		{
			ft_printf("[");
			ft_putstrs_fd(tok->value, ", ", STDOUT_FILENO);
			ft_printf("]");
		}
		else
			ft_printf("[NULL]");
		ft_printf("\n");
		list = list->next;
	}
}
