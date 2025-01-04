/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 22:15:51 by ymizukam          #+#    #+#             */
/*   Updated: 2025/01/05 05:21:05 by teando           ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "ft_system.h"
#include "ft_token.h"
#include "xunistd.h"

char **convert_argv(t_list *lst)
{
	char **cargv;
	t_token *token;
	size_t i;

	if (!lst || !lst->data)
		return (NULL);
	cargv = ft_calloc(ft_lstsize(lst) + 1, sizeof(char *));
	if (!cargv)
		return (NULL);
	i = 0;
	while (lst)
	{
		token = lst->data;
		if (!token || !token->value)
			return (ft_strs_clear(cargv), NULL);
		cargv[i] = ft_strdup(token->value);
		if (!cargv[i])
			return (ft_strs_clear(cargv), NULL);
		i++;
		lst = lst->next;
	}
	cargv[i] = NULL;
	return (cargv);
}

void token_clear(void *ptr)
{
	t_token *token;

	token = (t_token *)ptr;
	if (token == NULL)
		return;
	if (token->value)
		free(token->value);
	free(token);
}
