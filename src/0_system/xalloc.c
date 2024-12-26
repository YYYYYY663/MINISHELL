/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xalloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymizukam <ymizukam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 21:27:29 by teando            #+#    #+#             */
/*   Updated: 2024/12/24 20:16:05 by ymizukam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_system.h"

void	*xmalloc(size_t size, t_info *info)
{
	#ifdef FUNC_OUT
		printf("%s\n",__func__);
	#endif
	char	*memory;

	memory = malloc(size);
	if (!memory)
	{
		system_exit(info, E_ALLOCATE);
	}
	ft_bzero(memory, size);
	return ((void *)memory);
}

t_list	*xlstnew(char *data, t_info *info)
{
	#ifdef FUNC_OUT
		printf("%s\n",__func__);
	#endif
	t_list	*list;

	list = ft_lstnew((void *)data);
	if (!list)
		system_exit(info, E_ALLOCATE);
	return (list);
}

// t_list	*xlst_from_strs(char **strs, t_info *info)
// {
// 	t_list	*list;

// 	list = ft_list_from_strs(strs);
// 	if (!list)
// 		system_exit(info, E_ALLOCATE);
// 	return (list);
// }

// char	**xlst_to_strs(t_list *lst, t_info *info)
// {
// 	char	**strs;

// 	strs = ft_list_to_strs(lst);
// 	if (!strs)
// 		system_exit(info, E_ALLOCATE);
// 	return (strs);
// }

// char	**xsplit(char *str, char sep, t_info *info)
// {
// 	char	**split;

// 	split = ft_split(str, sep);
// 	if (!split)
// 		system_exit(info, E_ALLOCATE);
// 	return (split);
// }
