/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   system_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymizukam <ymizukam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 16:33:27 by ymizukam          #+#    #+#             */
/*   Updated: 2024/12/22 16:33:29 by ymizukam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_system.h"

t_info *system_init(char **envp)
{
	t_info *info;

	info = ft_calloc(sizeof(t_info), 1);
	if (!info)
		return (NULL);
	(void)envp;
	// info->env_map = x_lst_from_strs(envp);
	// getcwd(info->cwd, PATH_MAX);
	return (info);
}

void system_deinit(t_info *info)
{
	if (!info)
		return;
	free(info->source_line);
	if (!info->token_list)
		ft_lstclear(&info->token_list, free);
	if (!info->env_map)
		ft_lstclear(&info->env_map, free);
	// ast_clear(info->ast);
	free(info);
}
