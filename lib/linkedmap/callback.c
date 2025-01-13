/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _env_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymizukam <ymizukam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 19:48:26 by ymizukam          #+#    #+#             */
/*   Updated: 2025/01/05 21:54:58 by ymizukam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lmap.h"

/**
 * @brief 環境変数のキーを比較する
 * 
 * この関数は以下の処理を行います：
 * 1. キーに'='を追加して一意な形式に変換
 * 2. 変換したキーと環境変数エントリを比較
 * 
 * @param data 環境変数エントリ
 * @param key 比較するキー
 * @return int 0:一致、その他:不一致
 */
int	default_cmp(void *data, void *key)
{
	char	uniq_key[PATH_MAX];

	ft_strlcpy(uniq_key, key, PATH_MAX);
	ft_strlcat(uniq_key, "=", PATH_MAX);
	return (ft_strncmp((char *)data, (char *)uniq_key,
			ft_strlen((char *)uniq_key)));
}
