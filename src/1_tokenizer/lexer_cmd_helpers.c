/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_cmd_helpers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 05:13:53 by teando            #+#    #+#             */
/*   Updated: 2024/12/23 05:15:51 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lexer.h"

/* ------------------ parse_one_command のヘルパー ------------------ */

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
