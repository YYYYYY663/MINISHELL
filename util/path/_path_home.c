/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _path_home.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymizukam <ymizukam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 17:07:04 by ymizukam          #+#    #+#             */
/*   Updated: 2025/01/14 13:02:45 by ymizukam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "path.h"
#include "variable.h"

/**
 * @brief チルダ（~）をホームディレクトリに展開する
 *
 * この関数は以下の処理を行います：
 * 1. HOME環境変数の値を取得
 * 2. チルダを除いたパスをHOMEの値と結合
 * 3. 結合したパスのアクセス権限をチェック
 *
 * @param path 解決されたパスを格納する配列
 * @param src チルダを含むパス
 * @param mode アクセス権限フラグ
 * @param info シェル情報構造体
 * @return int 0:成功、-1:失敗
 */
int	_resolve_path_home(char path[], char *src, int mode, t_info *info)
{
	char	*home;

	home = var_get("HOME", info);
	ft_strlcpy(path, home, PATH_MAX);
	ft_strlcat(path, src + 1, PATH_MAX);
	free(home);
	return (access(path, mode));
}
