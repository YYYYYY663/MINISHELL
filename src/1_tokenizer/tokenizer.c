/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 04:10:42 by teando            #+#    #+#             */
/*   Updated: 2024/12/23 19:00:00 by teando           ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "ft_lexer.h"

t_status xlexer(t_info *info)
{
	info->token_list = NULL;
	info->status = E_NONE;
	if (!info->source_line)
		return (info->status);
	if (!tokenize_line(info))
	{
		if (info->status == E_NONE)
			info->status = E_SYNTAX;
		return (info->status);
	}
	if (!validate_syntax(info))
		return (info->status);
	return (info->status);
}

static const char *type_to_str(t_token_type t)
{
	if (t == TT_WORD)
		return "TT_WORD";
	if (t == TT_PIPE)
		return "TT_PIPE";
	if (t == TT_REDIR_IN)
		return "TT_REDIR_IN";
	if (t == TT_APPEND)
		return "TT_APPEND";
	if (t == TT_REDIR_OUT)
		return "TT_REDIR_OUT";
	if (t == TT_HEREDOC)
		return "TT_HEREDOC";
	if (t == TT_LPAREN)
		return "TT_LPAREN";
	if (t == TT_RPAREN)
		return "TT_RPAREN";
	if (t == TT_AND_AND)
		return "TT_AND_AND";
	if (t == TT_OR_OR)
		return "TT_OR_OR";
	if (t == TT_SEMICOLON)
		return "TT_SEMICOLON";
	if (t == TT_EOF)
		return "TT_EOF";
	return "TT_ERROR";
}

void debug_print_token_list(t_list *list)
{
	t_token *tok;

	while (list)
	{
		tok = (t_token *)list->data;
		ft_printf("type: %s, value: ", type_to_str(tok->type));
		if (tok->value)
			ft_printf("[%s]\n", tok->value);
		else
			ft_printf("NULL\n");
		list = list->next;
	}
}
