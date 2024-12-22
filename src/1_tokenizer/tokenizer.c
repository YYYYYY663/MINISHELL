/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 04:10:42 by teando            #+#    #+#             */
/*   Updated: 2024/12/23 04:10:48 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lexer.h"

t_status	xlexer(t_info *info)
{
	info->token_list = NULL;
	info->status = E_NONE;
	if (!info->source_line)
		return (info->status);
	if (!tokenize_line(info) && info->status == E_NONE)
		info->status = E_SYNTAX;
	return (info->status);
}

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
			ft_strs_clear(tok->value);
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
			ft_printf("[NULL]");
		ft_printf("\n");
		list = list->next;
	}
}
