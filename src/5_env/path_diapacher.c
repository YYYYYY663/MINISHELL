/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_diapacher.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymizukam <ymizukam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 16:58:58 by ymizukam          #+#    #+#             */
/*   Updated: 2025/01/15 20:43:53 by ymizukam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_env.h"

int	_resolve_path_current(char path[], char *src, int mode, t_info *info)
{
	ft_strlcpy(path, info->cwd, PATH_MAX);
	ft_strlcat(path, "/", PATH_MAX);
	ft_strlcat(path, src, PATH_MAX);
	return (access(path, mode));
}
/**
 * @brief パスのサニタイズ
 * //tmp//////  -> /tmp
 *
 */
void	normalize_path(char path[], char *src)
{
	// while (*src && *src ==)
	ft_strlcpy(path, src, PATH_MAX);
}

/**
 * @brief パスの種類を判別し、適切な解決方法を選択する
 *
 * この関数は以下の処理を行います：
 * 1. パスの先頭文字を確認し、以下の種類に分類：
 *    - 絶対パス（'/'で始まる）
 *    - ホームディレクトリ（'~'で始まる）
 *    - 相対パス（'.'で始まる）
 *    - その他（PATHから検索）
 * 2. 各種類に応じた解決関数を呼び出す
 *
 * @param path 解決されたパスを格納する配列
 * @param src 元のパス文字列
 * @param mode アクセス権限フラグ
 * @param info シェル情報構造体
 * @return int 0:成功、-1:失敗
 */
int	path_dispacher(char path[], char *src, int mode, t_info *info)
{
	char	normalized_src[PATH_MAX];

	path[0] = '\0';
	normalize_path(normalized_src, src);
	// F_OK /../などを弾けていない
	if (normalized_src[0] == '/' && access(normalized_src, mode) == 0)
		return (ft_strlcpy(path, normalized_src, PATH_MAX), access(path, mode));
	if (normalized_src[0] == '~')
		return (_resolve_path_home(path, normalized_src, mode, info));
	if (normalized_src[0] == '.')
		return (_resolve_path_relative(path, normalized_src, mode, info));
	if (mode == X_OK)
		return (_resolve_path_cmd(path, normalized_src, mode, info));
	return (_resolve_path_current(path, normalized_src, mode, info));
}
