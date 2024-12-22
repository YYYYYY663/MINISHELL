/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocate_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 04:17:08 by teando            #+#    #+#             */
/*   Updated: 2024/12/23 04:32:23 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lexer.h"

/*
** ========= トークン生成系 ===========
** create_token, add_token
*/

/* --- t_token を新規作成 --- */
t_token	*create_token(t_token_type type, char **value, t_info *info)
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
int	add_token(t_info *info, t_token *tok)
{
	t_list	*node;
	t_list	*tmp;

	if (!tok)
		return (0);
	node = ft_lstnew(tok);
	if (!node)
	{
		ft_strs_clear(tok->value);
		free(tok);
		return (0);
	}
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
