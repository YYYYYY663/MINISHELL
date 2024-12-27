/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _path_absolute.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymizukam <ymizukam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 22:06:10 by ymizukam          #+#    #+#             */
/*   Updated: 2024/12/22 17:06:17 by ymizukam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_env.h"
#include "ft_system.h"

int	_resolve_path_absolute(char path[], char *src, int mode, t_info *info)
{
	char *path_candidate = env_get("PATH", info);
	char **path_candidates = ft_split(path_candidate,':'); 
	int index = 0;
	while(path_candidates[index])
	{
		ft_strlcpy(path, path_candidates[index], PATH_MAX);
		ft_strlcat(path, "/", PATH_MAX);
		ft_strlcat(path, src, PATH_MAX);
		if (access(path, mode) == 0)
			break;
		index++;
	}
	free(path_candidate);
	ft_strs_clear(path_candidates);
	return (access(path, mode));
}

// t_status	xabsolute_path(char *dstpath, char *srcpath, t_list *env_map,
// 		int mode)
// {
// 	char	*envpathes;

// 	envpathes = env_get(env_map, "PATH");
// 	ft_strlcpy(dstpath, envpathes, PATH_MAX);
// 	ft_strlcat(dstpath, "/", PATH_MAX);
// 	ft_strlcat(dstpath, srcpath, PATH_MAX);
// 	return (E_NONE);
// }
