/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymizukam <ymizukam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 19:48:52 by ymizukam          #+#    #+#             */
/*   Updated: 2025/01/04 22:07:53 by ymizukam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lmap.h"

void	lmap_export(char *key, char *value, t_lmap *lmap, int (*cmp)(void *,void *))
{
	char	*ent;
    int entlen = ft_strlen(key) + ft_strlen(value) + 2;
    ent = malloc(entlen);
	ft_strlcpy(ent, key, entlen);
	ft_strlcat(ent, "=", entlen);
	ft_strlcat(ent, value, entlen);
    if (!cmp)
        cmp = default_cmp;
	t_list *lst = ft_list_find(lmap, key, cmp);
	if (lst)
	{
		free(lst->data);
		lst->data = ft_strdup(ent);
		return;
    }
    lst = ft_lstnew(ent);
	ft_lstadd_back(&lmap, lst);
}

