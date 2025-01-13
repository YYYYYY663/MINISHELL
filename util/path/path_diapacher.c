/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_diapacher.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymizukam <ymizukam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 16:58:58 by ymizukam          #+#    #+#             */
/*   Updated: 2025/01/04 22:08:12 by ymizukam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "path.h"

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
	path[0] = '\0';
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
