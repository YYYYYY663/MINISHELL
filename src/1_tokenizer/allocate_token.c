/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocate_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 04:17:08 by teando            #+#    #+#             */
/*   Updated: 2024/12/23 19:00:06 by teando           ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "ft_lexer.h"

t_token *create_token(t_token_type type, char *value, t_info *info)
{
	t_token *tok;

	tok = (t_token *)xmalloc(sizeof(t_token), info);
	if (!tok)
		return (NULL);
	tok->type = type;
	tok->value = value;
	return (tok);
}

int add_token(t_info *info, t_token *tok)
{
	t_list *node;
	t_list *tmp;

	if (!tok)
		return (0);
	node = ft_lstnew(tok);
	if (!node)
	{
		free(tok->value);
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

void token_list_free(t_list **token_list)
{
	t_list *cur;
	t_list *nx;
	t_token *tok;

	cur = *token_list;
	while (cur)
	{
		nx = cur->next;
		tok = (t_token *)cur->data;
		if (tok)
		{
			free(tok->value);
			free(tok);
		}
		free(cur);
		cur = nx;
	}
	*token_list = NULL;
}
