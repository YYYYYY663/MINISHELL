/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 15:29:01 by teando            #+#    #+#             */
/*   Updated: 2024/12/23 03:24:39 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lexer.h"

/************************************
 * 文字列配列操作のヘルパー
 ************************************/
static char	**make_str_array1(const char *s)
{
	char	**arr;

	arr = (char **)malloc(sizeof(char *) * 2);
	if (!arr)
		return (NULL);
	arr[0] = ft_strdup(s ? s : "");
	if (!arr[0])
	{
		free(arr);
		return (NULL);
	}
	arr[1] = NULL;
	return (arr);
}

static char	**append_str_to_array(char **arr, const char *s)
{
	size_t	len;
	char	**newarr;

	if (!s)
		return (arr);
	if (!arr)
		return (make_str_array1(s));
	len = 0;
	while (arr[len])
		len++;
	newarr = (char **)malloc(sizeof(char *) * (len + 2));
	if (!newarr)
		return (NULL);
	for (size_t i = 0; i < len; i++)
		newarr[i] = arr[i];
	newarr[len] = ft_strdup(s);
	newarr[len + 1] = NULL;
	free(arr);
	return (newarr);
}

static void	free_str_array(char **arr)
{
	if (!arr)
		return ;
	for (size_t i = 0; arr[i]; i++)
		free(arr[i]);
	free(arr);
}

/************************************
 * トークン生成
 ************************************/
static t_token	*create_token(t_token_type type, char **value)
{
	t_token	*tok;

	tok = malloc(sizeof(t_token));
	if (!tok)
	{
		free_str_array(value);
		return (NULL);
	}
	tok->type = type;
	tok->value = value;
	return (tok);
}

static int	add_token(t_info *info, t_token *tok)
{
	t_list	*node;
	t_list	*tmp;

	if (!tok)
		return (0);
	node = malloc(sizeof(t_list));
	if (!node)
	{
		free_str_array(tok->value);
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

/************************************
 * 演算子判定
 ************************************/
static t_token_type	get_redirect_type(const char *s, size_t *len)
{
	if (ft_strncmp(s, ">>", 2) == 0)
	{
		if (len)
			*len = 2;
		return (TT_APPEND);
	}
	if (ft_strncmp(s, "<<", 2) == 0)
	{
		if (len)
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
	if (ft_strncmp(s, "&&", 2) == 0)
	{
		if (len)
			*len = 2;
		return (TT_AND_AND);
	}
	if (ft_strncmp(s, "||", 2) == 0)
	{
		if (len)
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

/************************************
 * コマンド区切り演算子かどうか
 ************************************/
static int	is_cmd_delimiter(char c)
{
	// ここでは |, ;, (, ), \0 を例示
	// &&, || は2文字チェックが必要なので
	// 実際にはもう少し考慮が必要
	if (c == '\0')
		return (1);
	if (c == '|' || c == ';' || c == '(' || c == ')')
		return (1);
	return (0);
}

/************************************
 * クォート読み取り
 ************************************/
static char	*read_quoted(const char *line, size_t *pos, t_info *info)
{
	size_t	start;
	char	*content;

	char quote_char = line[*pos]; // ' or "
	start = (*pos) + 1;
	(*pos)++;
	while (line[*pos] && line[*pos] != quote_char)
		(*pos)++;
	if (!line[*pos])
	{
		info->status = E_SYNTAX;
		return (NULL);
	}
	content = ft_substr(line, start, (*pos) - start);
	(*pos)++; // 終端クォートをスキップ
	return (content);
}

/************************************
 * リダイレクトをパースして
 * そのトークンを返す
 ************************************/
static t_token	*parse_redirect(const char *line, size_t *pos)
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
	// 後続の空白スキップ
	while (ft_isspace(line[*pos]))
		(*pos)++;
	// ファイル名を(空白 or 演算子 or 区切りに当たるまで)取得
	start = *pos;
	while (line[*pos])
	{
		if (ft_isspace(line[*pos]) || is_cmd_delimiter(line[*pos]))
			break ;
		// 2文字/1文字 演算子やリダイレクトが始まったら break
		if (get_two_char_op(&line[*pos], NULL) != TT_ERROR)
			break ;
		if (get_one_char_op(line[*pos]) != TT_ERROR)
			break ;
		if (get_redirect_type(&line[*pos], NULL) != TT_ERROR)
			break ;
		(*pos)++;
	}
	fname = ft_substr(line, start, (*pos) - start);
	// value = [">", "x"], [">>", "filename"], etc.
	arr = NULL;
	arr = append_str_to_array(arr, op_str);
	if (fname && *fname)
		arr = append_str_to_array(arr, fname);
	free(op_str);
	free(fname);
	return (create_token(rtype, arr));
}

/************************************
 * 1コマンドをパースする
 * - 引数は cmd_argv に貯める
 * - リダイレクトは redir_list に貯めておいて、
 *   最後にまとめて token_list に繋ぐ
 ************************************/
static int	parse_one_command(const char *line, size_t *pos, t_info *info)
{
	t_token	*r_tok;
	t_list	*n;
	t_list	*tmp;
	char	*q;
	size_t	start;
	size_t	length;
	char	*seg;
	t_token	*cmd_tok;
	t_list	*cur;
	t_list	*nx;

	char **cmd_argv = NULL;    // コマンド引数たち
	t_list *redir_list = NULL; // リダイレクトトークンをつなぐリスト
	while (1)
	{
		// 空白スキップ
		while (ft_isspace(line[*pos]))
			(*pos)++;
		// コマンド区切り or 行末なら終了
		if (is_cmd_delimiter(line[*pos]))
			break ;
		// 2文字演算子(&&, ||)のチェック
		if (get_two_char_op(&line[*pos], NULL) != TT_ERROR)
			break ; // コマンド区切りとして扱うなら
		// リダイレクト？
		if (get_redirect_type(&line[*pos], NULL) != TT_ERROR)
		{
			// ここでは“すぐに add_token”しないで、
			// redir_list にだけ繋いでおく
			r_tok = parse_redirect(line, pos);
			if (!r_tok)
			{
				free_str_array(cmd_argv);
				return (0);
			}
			// redir_list へ追加
			n = malloc(sizeof(t_list));
			if (!n)
			{
				free_str_array(r_tok->value);
				free(r_tok);
				free_str_array(cmd_argv);
				return (0);
			}
			n->data = r_tok;
			n->next = NULL;
			// append to redir_list
			if (!redir_list)
				redir_list = n;
			else
			{
				tmp = redir_list;
				while (tmp->next)
					tmp = tmp->next;
				tmp->next = n;
			}
			continue ;
		}
		// 通常の単語 or クォート
		if (line[*pos] == '"' || line[*pos] == '\'')
		{
			q = read_quoted(line, pos, info);
			if (!q)
			{
				free_str_array(cmd_argv);
				// redir_listの開放も必要
				return (0);
			}
			cmd_argv = append_str_to_array(cmd_argv, q);
			free(q);
		}
		else
		{
			// 空白・演算子・区切りに当たるまでを1単語取得
			start = *pos;
			while (line[*pos])
			{
				if (ft_isspace(line[*pos]) || is_cmd_delimiter(line[*pos]))
					break ;
				if (get_two_char_op(&line[*pos], NULL) != TT_ERROR)
					break ;
				if (get_one_char_op(line[*pos]) != TT_ERROR)
					break ;
				if (get_redirect_type(&line[*pos], NULL) != TT_ERROR)
					break ;
				(*pos)++;
			}
			length = (*pos) - start;
			if (length > 0)
			{
				seg = ft_substr(line, start, length);
				cmd_argv = append_str_to_array(cmd_argv, seg);
				free(seg);
			}
		}
		// エラー処理
		if (info->status != E_NONE)
		{
			free_str_array(cmd_argv);
			// redir_listもfree必要
			return (0);
		}
	}
	// ここでコマンドの単語が一つでもあればコマンドトークン生成
	if (cmd_argv)
	{
		cmd_tok = create_token(TT_CMD, cmd_argv);
		if (!cmd_tok || !add_token(info, cmd_tok))
		{
			// メモリ解放等
			return (0);
		}
	}
	else
	{
		// cmd_argvが無い(空) = 引数無しのコマンドかもしれない
		// たとえば行頭で区切りにぶつかった場合など
		// ここで何もしない or ダミーtoken作る等、要件次第
	}
	// 続いて、溜め込んでいたリダイレクトトークンを「まとめて」追加
	// 順番は入力に出現した順をキープ
	{
		cur = redir_list;
		while (cur)
		{
			nx = cur->next;
			r_tok = (t_token *)cur->data;
			// r_tok はすでに中身あり
			if (!add_token(info, r_tok))
			{
				// エラー処理
				free(cur);
				// 残りのノードもfree
				return (0);
			}
			// リダイレクトトークンは既にtoken_listにつながった
			free(cur);
			cur = nx;
		}
	}
	return (1);
}

/************************************
 * 演算子トークン (パイプ, ;など)
 ************************************/
static t_token	*get_operator_token(const char *line, size_t *pos)
{
	size_t			len;
	t_token_type	opt;
	char			*op_str;
	char			**arr;

	len = 0;
	opt = get_two_char_op(&line[*pos], &len);
	if (opt != TT_ERROR)
	{
		op_str = ft_substr(line, *pos, len);
		(*pos) += len;
		arr = make_str_array1(op_str);
		free(op_str);
		return (create_token(opt, arr));
	}
	opt = get_one_char_op(line[*pos]);
	if (opt != TT_ERROR)
	{
		len = 1;
		op_str = ft_substr(line, *pos, len);
		(*pos)++;
		arr = make_str_array1(op_str);
		free(op_str);
		return (create_token(opt, arr));
	}
	return (NULL);
}

/************************************
 * tokenize_line (メインループ)
 ************************************/
static int	tokenize_line(t_info *info)
{
	size_t		i;
	const char	*line = info->source_line;
	t_token		*op_tok;
	char		**arr;
	t_token		*eof_token;

	i = 0;
	while (1)
	{
		// 空白スキップ
		while (ft_isspace(line[i]))
			i++;
		if (line[i] == '\0')
			break ;
		// 1コマンドを parse
		if (!parse_one_command(line, &i, info))
			return (0);
		if (info->status != E_NONE)
			return (0);
		// parse_one_command を抜けたら、いま指している文字が
		// 区切り演算子(|, ;, &&, ||, ...) か、'\0' か
		if (line[i] != '\0')
		{
			// 区切り演算子トークンを作ってリストに追加
			op_tok = get_operator_token(line, &i);
			if (op_tok)
			{
				if (!add_token(info, op_tok))
					return (0);
			}
		}
		if (line[i] == '\0')
			break ;
	}
	// 最後に EOF トークンを追加
	{
		arr = make_str_array1("EOF");
		eof_token = create_token(TT_EOF, arr);
		if (!eof_token || !add_token(info, eof_token))
			return (0);
	}
	return (1);
}

/************************************
 * xlexer (外部インターフェース)
 ************************************/
t_status	xlexer(t_info *info)
{
	info->token_list = NULL;
	info->status = E_NONE;
	if (!info->source_line)
		return (info->status);
	if (!tokenize_line(info))
	{
		if (info->status == E_NONE)
			info->status = E_SYNTAX;
	}
	return (info->status);
}

/************************************
 * token_list_free / debug_print
 ************************************/
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
			free_str_array(tok->value);
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
		{
			ft_printf("[NULL]");
		}
		ft_printf("\n");
		list = list->next;
	}
}
