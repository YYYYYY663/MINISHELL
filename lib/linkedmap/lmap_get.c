/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lmap_get.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymizukam <ymizukam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 19:48:44 by ymizukam          #+#    #+#             */
/*   Updated: 2025/01/14 13:07:39 by ymizukam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lmap.h"

char	*lmap_get(char *key, t_lmap *lmap, int (*cmp)(void *, void *))
{
	if (!key || !lmap)
		return (NULL);
	if (!cmp)
		cmp = default_cmp;
	t_list *lst;
	lst = ft_list_find((t_list *)lmap, key, cmp);
	if (!lst)
		return (NULL);
	return (ft_substr_r(lst->data, '='));
}