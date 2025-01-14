/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_get.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymizukam <ymizukam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 19:48:44 by ymizukam          #+#    #+#             */
/*   Updated: 2025/01/14 12:40:11 by ymizukam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "variable.h"

/**
 * @brief 環境変数の値を取得する
 *
 * この関数は以下の処理を行います：
 * 1. 特殊な1文字キーの場合、特殊環境変数配列から値を取得
 * 2. 通常の環境変数の場合：
 *    - 環境変数リストから指定されたキーを検索
 *    - キーが見つからない場合は空文字列を返す
 *    - キーが見つかった場合は値を抽出して返す
 *
 * @param key 取得する環境変数のキー
 * @param info シェル情報構造体
 * @return char* 環境変数の値（見つからない場合は空文字列）
 */
char	*var_get(char *key, t_info *info)
{
	char *value;

	if (ft_strlen(key) == 1 && info->env_spc[(unsigned char)*key])
		return (info->env_spc[(unsigned char)*key]);
	value = lmap_get(key, info->env_map, NULL);
	if (!value)
		return (ft_strdup(""));
	return (value);
}