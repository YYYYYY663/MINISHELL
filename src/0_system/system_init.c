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
#include "ft_token.h"
#include "xunistd.h"


t_info *system_init(char **envp)
{
	#ifdef FUNC_OUT
		printf("%s\n",__func__);
	#endif
	t_info *info;

	info = ft_calloc(sizeof(t_info), 1);
	if (!info)
		return (NULL);
	
	info->env_map = ft_list_from_strs(envp);
	if(getcwd(info->cwd, PATH_MAX) == NULL)
	{
		perror("pwd");
		system_exit(info, 1);
	}
	// info->stdin_backup = dup(STDIN_FILENO);
	// info->stdout_backup = dup(STDOUT_FILENO);
	info->env_spc['?'] = ft_itoa(0);
	
	return (info);
}

void line_init(t_info *info)
{
	if (!info)
		exit(1);
	free(info->source_line);
	if (info->token_list != NULL)
	{
		//ft_lstclear(&info->token_list, &token_clear);でも動く。。。謎
		ft_lstclear(&info->token_list, token_clear);
	}
	ast_clear(info->ast);
	info->env_spc['?'] = ft_itoa(info->status);
	info->status = 0;
	
}

