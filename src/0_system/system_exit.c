/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   system_exit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymizukam <ymizukam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 21:27:54 by teando            #+#    #+#             */
/*   Updated: 2025/01/04 23:50:07 by ymizukam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_system.h"
#include "xunistd.h"

void	system_exit(t_info *info, t_status status)
{
	int	i;

#ifdef FUNC_OUT
	printf("%s\n", __func__);
#endif
	line_init(info);
	i = 0;
	while (i < 128)
		free(info->env_spc[i++]);
	ft_lstclear(&info->env_map, free);
	free(info);
	exit(status);
}
