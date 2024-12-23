/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 14:07:53 by teando            #+#    #+#             */
/*   Updated: 2024/12/23 15:47:43 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lexer.h"

/*
** ========= quoted文字列を1トークンに分解、コマンド引数に追加 handle_quoted ===========
**
**   line: 1行の文字列
**   i: line[]の現在のインデックス
**   info: system_info
**   cmd_argv: コマンド引数の配列
**
**   quoted文字列を1トークンに分解し、コマンド引数に追加する。
**   syntax errorが起きた場合はinfo->statusにE_SYNTAXを設定し、0を返す。
**   それ以外は、(*i)++を行い1を返す。
*/
int	handle_quoted(const char *line, size_t *i, t_info *info, char ***cmd_argv)
{
	char	quote;
	size_t	start;
	char	*content;

	quote = line[*i];
	start = *i + 1;
	(*i)++;
	while (line[*i] && line[*i] != quote)
		(*i)++;
	if (!line[*i])
	{
		info->status = E_SYNTAX;
		return (ft_strs_clear(*cmd_argv), 0);
	}
	content = ft_substr(line, start, (*i) - start);
	if (!content)
		return (ft_strs_clear(*cmd_argv), 0);
	*cmd_argv = strs_append(*cmd_argv, content, info);
	free(content);
	(*i)++;
	return (1);
}

/*
** ========= Redirectトークンを1トークンに分解、redir_listに追加 handle_redirect ===========
**
**   line: 1行の文字列
**   i: line[]の現在のインデックス
**   info: system_info
**   redir_list: Redirectトークンのリスト
**
**   Redirectトークンを1トークンに分解し、redir_listに追加する。
**   syntax errorが起きた場合はinfo->statusにE_SYNTAXを設定し、0を返す。
**   それ以外は、(*i)++を行い1を返す。
*/
int	handle_redirect(const char *line, size_t *i, t_info *info, t_list **redir)
{
	t_token	*redir_tok;
	t_list	*node;

	redir_tok = parse_redirect(line, i, info);
	if (!redir_tok)
		return (0);
	node = ft_lstnew(redir_tok);
	if (!node)
	{
		free(redir_tok->value);
		free(redir_tok);
		return (0);
	}
	ft_lstadd_back(redir, node);
	return (1);
}

/*
** ========= 1つのwordをパースしcmd_argvに追加 handle_word ===========
**
**   line: 1行の文字列
**   i: line[]の現在のインデックス
**   info: system_info
**   cmd_argv: wordのリスト
**
**   1つのwordをパースしcmd_argvに追加する
**   syntax errorが起きた場合はinfo->statusにE_SYNTAXを設定し、0を返す
**   それ以外は、(*i)++を行い1を返す
*/
int	handle_word(const char *line, size_t *i, t_info *info, char ***cmd_argv)
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
