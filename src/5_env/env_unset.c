/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymizukam <ymizukam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 19:48:35 by ymizukam          #+#    #+#             */
/*   Updated: 2024/12/20 05:14:50 by ymizukam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_env.h"

// keyを削除
t_status	env_unset(char *key,  t_info *info)
{
	t_list	*lst;

	ft_list_remove_if(&info->env_map, key, __cmp, free);
	return (E_NONE);
}

// void	ft_list_remove_if(t_list **begin_list, void *data_ref,
// int (*cmp)(void *, void *),
// 		void (*free_fct)(void *))
// {
// 	t_list	*current;
// 	t_list	*prev;
// 	t_list	*tmp;

// 	current = *begin_list;
// 	prev = 0;
// 	while (current)
// 	{
// 		if ((*cmp)(current->data, data_ref) == 0)
// 		{
// 			tmp = current->next;
// 			(*free_fct)(current->data);
// 			free(current);
// 			if (!prev)
// 				*begin_list = tmp;
// 			else
// 				prev->next = tmp;
// 			current = tmp;
// 		}
// 		else
// 		{
// 			prev = current;
// 			current = current->next;
// 		}
// 	}
// }
