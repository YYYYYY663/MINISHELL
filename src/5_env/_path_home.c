/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _path_home.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymizukam <ymizukam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 17:07:04 by ymizukam          #+#    #+#             */
/*   Updated: 2024/12/22 17:07:51 by ymizukam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_env.h"
#include "ft_system.h"

int	_resolve_path_home(char path[], char *src, int mode, t_info *info)
{
	ft_strlcpy(path, src, PATH_MAX);
	return (access(path, mode));
}