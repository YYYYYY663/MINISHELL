/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_diapatcher.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymizukam <ymizukam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 16:58:58 by ymizukam          #+#    #+#             */
/*   Updated: 2025/02/12 18:31:14 by ymizukam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_env.h"

int	_resolve_path_current(char path[], char *src, int mode, t_info *info)
{
	ft_strlcpy(path, info->cwd, PATH_MAX);
	if (ft_strcmp(path, "/"))
		ft_strlcat(path, "/", PATH_MAX);
	ft_strlcat(path, src, PATH_MAX);
	return (access(path, mode));
}
/**
 * @brief パスをuniqueにする
 * ///のように重なっていたら/にする
 * 最後の/を取る
 */
void	normalize_path(char *dst, char *src)
{
	char	*dstp;

	dstp = dst;
	if (ft_strncmp(src, "/", 2) == 0)
	{
		ft_strlcpy(dst, src, PATH_MAX);
		return ;
	}
	while (*src)
	{
		if (*src == '/')
		{
			while (*src == '/')
				src++;
			src--;
		}
		*dstp++ = *src++;
	}
	*dstp = '\0';
	if (dstp != dst && *--src == '/')
	{
		*--dstp = '\0';
	}
	printf("path %s\n", dst); // debug
}

/**
 * @brief パスの種類を判別し、適切な解決方法を選択する
 * X_OK && map_find(PATH)  相対パス、絶対パス、PATHから探す
 *　else 相対パス、絶対パス、CWDから探す
 * todo cd /bin/..など対応できていないのでslash区切りで解析したほうが良さそう
 * todo 今の実装ではcd ...などがエラーにならない
 */
int	path_dispatcher(char path[], char *src, int mode, t_info *info)
{
	char	normalized_src[PATH_MAX];

	path[0] = '\0';
	normalize_path(normalized_src, src);
	// F_OK /../などを弾けていない
	if (src[0] == '/')
		return (ft_strlcpy(path, normalized_src, PATH_MAX), access(path, mode));
	if (normalized_src[0] == '~')
		return (_resolve_path_home(path, normalized_src, mode, info));
	if (normalized_src[0] == '.')
		return (_resolve_path_relative(path, normalized_src, mode, info));
	if (mode == X_OK)
		return (_resolve_path_cmd(path, normalized_src, mode, info));
	return (_resolve_path_current(path, normalized_src, mode, info));
}
