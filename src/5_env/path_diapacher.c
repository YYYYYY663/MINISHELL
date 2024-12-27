/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_diapacher.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymizukam <ymizukam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 16:58:58 by ymizukam          #+#    #+#             */
/*   Updated: 2024/12/22 17:10:57 by ymizukam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_env.h"

int	path_dispacher(char path[], char *src, int mode, t_info *info)
{
	path[0] = '\0';
	//src[0] == '/'ない方が良いけどcdするときに必要
	if (src[0] == '/' && access(src, mode) == 0)
	{
		ft_strlcpy(path, src, PATH_MAX);
		return (access(path, mode));
	}
	if (src[0] == '~')
	{
		return (_resolve_path_home(path, src, mode, info));
	}
	if (src[0] == '.')
	{
		return (_resolve_path_relative(path, src, mode, info));
	}
	return (_resolve_path_absolute(path, src, mode, info));
}