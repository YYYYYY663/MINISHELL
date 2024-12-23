/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocate_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 04:17:08 by teando            #+#    #+#             */
/*   Updated: 2024/12/23 17:49:23 by teando           ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "ft_lexer.h"

t_token *create_token(t_token_type type, char *value, t_info *info)
{
	t_token *tok;

	(void)info;
	tok = (t_token *)ft_calloc(1, sizeof(t_token));
	if (!tok)
	{
		if (value)
			ft_strs_clear(value);
		return (NULL);
	}
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

static char **do_append(char **dst, char **src, const char *newstr, t_info *inf)
{
	size_t i;

	i = 0;
	while (src && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = ft_strdup(newstr);
	if (!dst[i])
	{
		ft_strs_clear(src);
		ft_strs_clear(dst);
		system_exit(inf, E_ALLOCATE);
	}
	dst[i + 1] = NULL;
	free(src);
	return (dst);
}

char **strs_append(char **src, const char *newstr, t_info *inf)
{
	char **dst;
	size_t len;

	if (!newstr)
		return (src);
	len = ft_count_strs(src);
	dst = ft_calloc(sizeof(char *), (len + 2));
	if (!dst)
	{
		ft_strs_clear(src);
		system_exit(inf, E_ALLOCATE);
	}
	return (do_append(dst, src, newstr, inf));
}
