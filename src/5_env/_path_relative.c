/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _path_relative.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymizukam <ymizukam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 17:06:28 by ymizukam          #+#    #+#             */
/*   Updated: 2024/12/22 17:08:04 by ymizukam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_env.h"
#include "ft_system.h"

int	_resolve_path_relative(char path[], char *src, int mode, t_info *info)
{
	ft_strlcpy(path, info->cwd, PATH_MAX);
	char *dotdot;
	while(1)
	{
		dotdot = ft_strnstr(src, "..",PATH_MAX);
		if (dotdot)
		{
			char *last_slash = ft_strrchr(path, '/');
			if (last_slash!= path)
				*last_slash = '\0';
			src = dotdot + ft_strlen("..");	
			continue;
		}
		if (*src == '.')
		{
			src++;
			continue;
		}
		break;
	}
	ft_strlcat(path, src, PATH_MAX);
	// printf("final %s\n", path);
	return (access(path, mode));
}


//cc _path_relative.c -DRELATIVE_TEST -I../../inc -I ../../lib/libft  ../../lib/libft/libft.a && ./a.out
#ifdef RELATIVE_TEST
int main()
{
	char path[PATH_MAX];
	t_info *info = malloc(sizeof(t_info));
	getcwd(info->cwd, PATH_MAX);
	//printf("cwd: %s\n",info->cwd);
	_resolve_path_relative(path, "./../Makefile", F_OK, info);
	perror(path);
}
#endif