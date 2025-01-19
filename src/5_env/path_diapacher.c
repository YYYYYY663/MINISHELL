/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_diapacher.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymizukam <ymizukam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 16:58:58 by ymizukam          #+#    #+#             */
/*   Updated: 2025/01/19 20:55:18 by ymizukam         ###   ########.fr       */
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
 * //tmp//////  -> /tmp
 *
 */
void	normalize_path(char dst[], char *src)
{
	// size_t	src_i;
	// size_t	dst_i;
	// src_i = 0;
	// dst_i = 0;
	// if (src[0] == '/')
	// {
	// 	dst[dst_i++] = '/';
	// 	while (src[++src_i] == '/')
	// 		;
	// }
	// while (src[src_i])
	// {
	// 	dst[dst_i++] = src[src_i++];
	// }
	// while (src_i > 0 && src[--src_i] == '/')
	// 	dst[--dst_i] = '\0';
	// dst[--dst_i] = '\0';
	// printf("path %s\n", dst);
	ft_strlcpy(dst, src, PATH_MAX);
}

/**
 * @brief パスの種類を判別し、適切な解決方法を選択する
 * X_OK && map_find(PATH)  相対パス、絶対パス、PATHから探す
 *　else 相対パス、絶対パス、CWDから探す
 * todo cd /bin/..など対応できていないのでslash区切りで解析したほうが良さそう
 * todo 今の実装ではcd ...などがエラーにならない
 */
int	path_dispacher(char path[], char *src, int mode, t_info *info)
{
	char	normalized_src[PATH_MAX];

	path[0] = '\0';
	normalize_path(normalized_src, src);
	// F_OK /../などを弾けていない
	if (normalized_src[0] == '/')
		return (ft_strlcpy(path, normalized_src, PATH_MAX), access(path, mode));
	if (normalized_src[0] == '~')
		return (_resolve_path_home(path, normalized_src, mode, info));
	if (normalized_src[0] == '.')
		return (_resolve_path_relative(path, normalized_src, mode, info));
	if (mode == X_OK)
		return (_resolve_path_cmd(path, normalized_src, mode, info));
	return (_resolve_path_current(path, normalized_src, mode, info));
}
