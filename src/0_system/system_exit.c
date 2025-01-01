/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   system_exit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 21:27:54 by teando            #+#    #+#             */
/*   Updated: 2024/12/17 23:05:08 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_system.h"
#include "xunistd.h"


void	system_exit(t_info *info, t_status status)
{
	#ifdef FUNC_OUT
		printf("%s\n",__func__);
	#endif

	line_init(info);
	int i = 0;
	while (i < 128)
		free(info->env_spc[i++]);
	ft_lstclear(&info->env_map, free);
	free(info);
	exit(status);
}



// void system_deinit(t_info *info)
// {
// 	#ifdef FUNC_OUT
// 		printf("%s\n",__func__);
// 	#endif
// 	if (!info)
// 		return;
// 	free(info->source_line);
// 	if (info->token_list != NULL)
// 	{
// 		//ft_lstclear(&info->token_list, &token_clear);でも動く。。。謎
// 		ft_lstclear(&info->token_list, token_clear);
// 	}
// 	if (info->env_map != NULL)
// 		ft_lstclear(&info->env_map, free);
// 	ast_clear(info->ast);
// 	#ifdef CLEAR_OUT
// 		printf("%s done\n",__func__);
// 	#endif
// 	free(info);

// }