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

#include "ft_env.h"

// keyから値を取得、なかったら""
char	*env_get(char *key, t_info *info)
{
	t_list	*lst;

	if (ft_strlen(key) == 1 && info->env_spc[(unsigned char)*key])
		return (info->env_spc[(unsigned char)*key]);
	lst = ft_list_find(info->env_map, key, __cmp);
	if (!lst)
		return (ft_strdup(""));
	return (ft_substr_r(lst->data, '='));
}
// char	*env_get(t_list *env, char *key)
// {
// 	t_list	*lst;

// 	lst = ft_list_find(env, key, __cmp);
// 	// note leak!!!MAX_PATHとして持っても良い
// 	if (!lst)
// 		return (ft_strdup(""));
// 	t_map *map = (t_map *)lst->data;
// 	if (!map)
// 		return (ft_strdup(""));
// 	return (ft_strdup(map->val));
// }
