/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymizukam <ymizukam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 22:15:51 by ymizukam          #+#    #+#             */
/*   Updated: 2025/01/05 02:43:01 by ymizukam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_system.h"
#include "ft_token.h"

char	**convert_argv(t_list *lst)
{
	char	**cargv;
	t_token	*token;
	char	**ptr;

	cargv = ft_calloc(ft_lstsize(lst) + 1, sizeof(char *));
	if (cargv == NULL)
		return (NULL);
	token = (t_token *)lst->data;
	ptr = cargv;
	while (lst != NULL)
	{
		*ptr++ = ft_strdup(token->value);
		lst = lst->next;
		token = (t_token *)lst->data;
	}
	return (cargv);
}

void	token_clear(void *ptr)
{
	t_token	*token;

	token = (t_token *)ptr;
	if (token == NULL)
		return ;
	if (token->value)
		free(token->value);
	free(token);
}
