/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_cmds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 15:29:01 by teando            #+#    #+#             */
/*   Updated: 2024/12/23 15:42:36 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lexer.h"

/*
** ========= filenameを1トークンに分解 read_filename ===========
**
**   line: 1行の文字列
**   pos: line[]の現在のインデックス
**
**   1つのfilenameをパースし、stringを返す
**   syntax errorが起きた場合はNULLを返す
*/
static char	*read_filename(const char *line, size_t *pos)
{
	size_t	len;
	char	*fname;

	// 区切り文字になるまで進める（スペースやリダイレクション記号など）
	// ft_strcspn は文字列中で任意の文字集合が最初に現れる位置までを取得
	// 区切り文字を " \t\n\v\f\r<>|&();" 等に
	len = ft_strcspn(&line[*pos], " \t\n\v\f\r|&()<>;");
	fname = ft_substr(line, *pos, len); // 開始位置は *pos で正しい
	*pos += len;
	return (fname);
}

/*
** ========= Redirectトークンを1トークンに分解 parse_redirect ===========
**
**   line: 1行の文字列
**   pos: line[]の現在のインデックス
**   info: system_info
**
**   Redirectトークンを1トークンに分解し、token_typeとfile nameを保持する。
**   syntax errorが起きた場合はinfo->statusにE_SYNTAXを設定し、NULLを返す。
**   それ以外は、(*i)++を行い、トークンを返す。
*/
t_token	*parse_redirect(const char *line, size_t *pos, t_info *info)
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

/*
** ========= redir_list全てをtoken_listに追加 flush_redir_list ===========
**
**   redir_list: Redirectトークンのリスト
**   info: system_info
**
**   redir_listの全ての要素をtoken_listに追加する。
**   syntax errorが起きた場合はinfo->statusにE_SYNTAXを設定し、0を返す。
**   それ以外は、1を返す。
*/
int	flush_redir_list(t_list **redir_list, t_info *info)
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

/*
** ========= 1つのcommandをパース parse_one_command ===========
**
**   line: 1行の文字列
**   i: line[]の現在のインデックス
**   info: system_info
**
**   1つのcommandをパースし、token_listに追加する。
**   syntax errorが起きた場合はinfo->statusにE_SYNTAXを設定し、0を返す。
**   それ以外は、(*i)++を行い1を返す。
*/
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

/*
** ========= 演算子トークン取得 get_operator_token ===========
**
**   line: 入力行の文字列
**   pos: 現在の文字位置
**   info: システム情報
**
**   1文字または2文字の演算子を解析し、対応するトークンを作成して返す
**   演算子が見つからない場合、NULLを返す
**   posは解析した演算子の長さ分進められる
*/
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
	arr = (char **)ft_calloc(sizeof(char *), 2);
	if (!arr)
		return (NULL);
	arr[0] = op_str;
	return (create_token(op, arr, info));
}
