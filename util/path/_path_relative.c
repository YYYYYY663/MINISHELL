/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _path_relative.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymizukam <ymizukam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 17:06:28 by ymizukam          #+#    #+#             */
/*   Updated: 2025/01/04 22:11:45 by ymizukam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "path.h"

/**
 * @brief 相対パスを絶対パスに解決する
 * 
 * この関数は以下の処理を行います：
 * 1. カレントディレクトリのパスを取得
 * 2. 相対パスの各要素を処理：
 *    - '..'：親ディレクトリに移動
 *    - '.'：現在のディレクトリを維持
 *    - その他：パスに追加
 * 3. 最終的な絶対パスを生成
 * 
 * @param path 解決されたパスを格納する配列
 * @param src 相対パス
 * @param mode アクセス権限フラグ
 * @param info シェル情報構造体
 * @return int 0:成功、-1:失敗
 */
int	_resolve_path_relative(char path[], char *src, int mode, t_info *info)
{
	char	*dotdot;
	char	*last_slash;

	ft_strlcpy(path, info->cwd, PATH_MAX);
	while (1)
	{
		dotdot = ft_strnstr(src, "..", PATH_MAX);
		if (dotdot)
		{
			last_slash = ft_strrchr(path, '/');
			if (last_slash != path)
				*last_slash = '\0';
			src = dotdot + ft_strlen("..");
			continue ;
		}
		if (*src == '.')
		{
			src++;
			continue ;
		}
		break ;
	}
	ft_strlcat(path, src, PATH_MAX);
	return (access(path, mode));
}

// cc _path_relative.c -DRELATIVE_TEST -I../../inc
//-I ../../lib/libft  ../../lib/libft/libft.a && ./a.out
// #ifdef RELATIVE_TEST
// int	main(void)
// {
// 	char	path[PATH_MAX];
// 	t_info	*info;

// 	info = malloc(sizeof(t_info));
// 	getcwd(info->cwd, PATH_MAX);
// 	// printf("cwd: %s\n",info->cwd);
// 	_resolve_path_relative(path, "./../Makefile", F_OK, info);
// 	perror(path);
// }
// #endif