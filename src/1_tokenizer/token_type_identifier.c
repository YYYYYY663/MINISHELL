/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_type_identifier.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 04:08:08 by teando            #+#    #+#             */
/*   Updated: 2024/12/23 17:47:11 by teando           ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "ft_lexer.h"

t_token_type get_two_char_op(const char *s, size_t *len)
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
	return (TT_ERROR);
}

t_token_type get_one_char_op(char c)
{
	if (c == '|')
		return (TT_PIPE);
	if (c == ';')
		return (TT_SEMICOLON);
	if (c == '>')
		return (TT_REDIR_IN);
	if (c == '<')
		return (TT_REDIR_OUT);
	return (TT_ERROR);
}
