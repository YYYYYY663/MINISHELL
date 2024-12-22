/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_redirect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 05:31:24 by teando            #+#    #+#             */
/*   Updated: 2024/12/23 05:37:48 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lexer.h"

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

int	handle_redirect(const char *line, size_t *i, t_info *info,
		t_list **redir_list)
{
	t_token	*redir_tok;

	redir_tok = parse_redirect(line, i, info);
	if (!redir_tok)
		return (0);
	ft_lstadd_back(redir_list, ft_lstnew(redir_tok));
	return (1);
}

/* ------------------ リダイレクトのフラッシュ処理 ------------------ */
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
