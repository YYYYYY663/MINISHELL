/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_type_identifier.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 04:08:08 by teando            #+#    #+#             */
/*   Updated: 2024/12/23 18:40:28 by teando           ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "ft_lexer.h"

t_token_type get_two_char_op(const char *s, size_t *len)
{
	if (!s || !s[0] || !s[1])
		return (TT_ERROR);
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

t_token_type get_one_char_op(char c)
{
	if (c == '>')
		return (TT_REDIR_OUT);
	if (c == '<')
		return (TT_REDIR_IN);
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
