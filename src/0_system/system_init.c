/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   system_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymizukam <ymizukam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 16:33:27 by ymizukam          #+#    #+#             */
/*   Updated: 2025/01/05 00:02:44 by ymizukam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_system.h"
#include "ft_token.h"
#include "xunistd.h"

t_info	*system_init(char **envp)
{
	t_info	*info;

#ifdef FUNC_OUT
	printf("%s\n", __func__);
#endif
	info = ft_calloc(sizeof(t_info), 1);
	if (!info)
		return (NULL);
	info->env_map = ft_list_from_strs(envp);
	if (getcwd(info->cwd, PATH_MAX) == NULL)
	{
		perror("pwd");
		system_exit(info, 1);
	}
	info->env_spc['?'] = ft_itoa(0);
	return (info);
}

void	line_init(t_info *info)
{
	if (!info)
		exit(1);
	xfree((void **)&info->source_line);
	if (info->token_list != NULL)
	{
		ft_lstclear(&info->token_list, token_clear);
	}
	ast_clear(info->ast);
	info->ast = NULL;
	free(info->env_spc['?']);
	info->env_spc['?'] = ft_itoa(info->status);
	info->status = 0;
}
