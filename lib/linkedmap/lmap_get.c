/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_get.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymizukam <ymizukam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 19:48:44 by ymizukam          #+#    #+#             */
/*   Updated: 2025/01/04 22:08:00 by ymizukam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lmap.h"


char	*lmap_get(char *key, t_lmap *lmap, int (*cmp)(void *,void *))
{
	if (!key || !lmap)
		return NULL;
    if (!cmp)
        cmp = default_cmp;
	t_list *lst = ft_list_find(lmap, key, cmp);
	if (!lst)
		return (NULL);
	return (ft_substr_r(lst->data, '='));
}