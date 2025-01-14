/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lmap_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymizukam <ymizukam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 19:48:52 by ymizukam          #+#    #+#             */
/*   Updated: 2025/01/14 13:04:07 by ymizukam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lmap.h"

void	lmap_export(char *key, char *value, t_lmap *lmap, int (*cmp)(void *,
			void *))
{
	char	*ent;
	int		entlen;
	t_list	*lst;

	entlen = ft_strlen(key) + ft_strlen(value) + 2;
	ent = malloc(entlen);
	if (!ent)
		return ;
	ft_strlcpy(ent, key, entlen);
	ft_strlcat(ent, "=", entlen);
	ft_strlcat(ent, value, entlen);
	if (!cmp)
		cmp = default_cmp;
	lst = ft_list_find((t_list *)lmap, key, cmp);
	if (lst)
	{
		free(lst->data);
		lst->data = ent;
		return ;
	}
	lst = ft_lstnew(ent);
	ft_lstadd_back(&lmap, lst);
}
