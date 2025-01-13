/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _path_absolute.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymizukam <ymizukam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 22:06:10 by ymizukam          #+#    #+#             */
/*   Updated: 2025/01/05 21:55:02 by ymizukam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "path.h"

/**
 * @brief PATH環境変数を使用して実行可能ファイルの絶対パスを解決する
 * 
 * この関数は以下の処理を行います：
 * 1. PATH環境変数の値を取得
 * 2. PATHをコロン区切りで分割
 * 3. 各ディレクトリに対して：
 *    - ソースパスと結合
 *    - アクセス権限をチェック
 *    - 実行可能な場合はそのパスを返す
 * 4. 見つからない場合は失敗を返す
 * 
 * @param path 解決されたパスを格納する配列
 * @param src コマンド名
 * @param mode アクセス権限フラグ
 * @param info シェル情報構造体
 * @return int 0:成功、-1:失敗
 */
int	_resolve_path_absolute(char path[], char *src, int mode, t_info *info)
{
	char	*path_candidate;
	char	**path_candidates;
	int		index;

	path_candidate = env_get("PATH", info);
	path_candidates = ft_split(path_candidate, ':');
	index = 0;
	while (path_candidates[index])
	{
		ft_strlcpy(path, path_candidates[index], PATH_MAX);
		ft_strlcat(path, "/", PATH_MAX);
		ft_strlcat(path, src, PATH_MAX);
		if (access(path, mode) == 0)
			break ;
		index++;
	}
	free(path_candidate);
	ft_strs_clear(path_candidates);
	return (access(path, mode));
}
