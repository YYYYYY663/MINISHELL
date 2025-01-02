/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymizukam <ymizukam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 19:48:52 by ymizukam          #+#    #+#             */
/*   Updated: 2024/12/20 05:21:22 by ymizukam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_env.h"


t_status	env_export(char *ent, t_info *info)
{
	char	key[PATH_MAX];
	char	*ent_cpy;
	int		delimiter;
	t_list	*lst;

	ent_cpy = ft_strdup(ent);
	if (ent_cpy == NULL)
		return (E_ALLOCATE);
	delimiter = ft_strcspn(ent, "=");
	//printf("delimiter: %d\n", delimiter);
	ft_strlcpy(key, ent, delimiter+1);
	if (_check_key(key))
		return (free(ent_cpy), E_ENV_KEY);



	lst = ft_list_find(info->env_map, key, __cmp);
	if (lst) //すでに存在する場合上書き
	{
		free(lst->data);
		lst->data = ent_cpy;
		return (E_NONE);
	}
	lst = ft_lstnew(ent_cpy);
	if (!lst)
		return (free(ent_cpy), E_ALLOCATE);
	ft_lstadd_back(&info->env_map, lst);
	return (E_NONE);
}

t_status env_export_item(char *key, char *value, t_info *info)
{
	char    ent[PATH_MAX];
	ft_strlcpy(ent, key, PATH_MAX);
	ft_strlcat(ent, "=",PATH_MAX);
    ft_strlcat(ent, value, PATH_MAX);
    return (env_export(ent, info));
}






// void map_append(t_info *info, char *key, char *val)
// {
// 	t_map *new = xmalloc(sizeof(t_map), info);
// 	new->key = key;
// 	new->val = val;
// 	lst = xlstnew(new, info);
// 	ft_lstadd_back(&info->env_map, lst);
// }

// t_status	env_export(t_info *info, char *key, char *val)
// {
// 	t_list	*lst;
// 	if (_check_key(info, key))
// 		xfree(&key);
// // 		return (free(ent_cpy), E_ENV_KEY);
// 	lst = ft_list_find(info->env_map, key, __cmp);
// 	if (lst) //すでに存在する場合上書き
// 	{
// 		xfree(&lst->data);
// 		lst->data = key;
// 		return (info->status);
// 	}
// 	map_append(info,key,val);
// 	// lst = ft_lstnew(ent_cpy);
// 	// ft_lstadd_back(&info->env_map, lst);
// 	return (E_NONE);
// }