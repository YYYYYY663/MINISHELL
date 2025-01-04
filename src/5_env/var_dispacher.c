/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_dispacher.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymizukam <ymizukam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 17:12:59 by ymizukam          #+#    #+#             */
/*   Updated: 2025/01/04 22:44:25 by ymizukam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_env.h"

/*
*""がついていたらWORD SPLITしない

*/

int	var_dispacher(t_list **lst, t_info *info)
{
	t_list	*head;
	t_token	*token;

	head = *lst;
	token = (t_token *)head->data;
	(void)info;
	while (head->next)
	{
		if (ft_strchr(token->value, '*'))
		{
			// expand_astarisk(&head, info);
			// DOUBLE QUOTE noexpand
		}
		if (ft_strchr(token->value, '$'))
		{
			// expand_dollar(&head, info);
			// SINGLE QUOTE no expand
			// DOUBLE QUOTE no word split
		}
		// head may change
		token = (t_token *)head->data;
		if (ft_strchr(token->value, '$') == NULL)
		{
			head = head->next;
			token = (t_token *)head->data;
		}
	}
	return (0);
}
