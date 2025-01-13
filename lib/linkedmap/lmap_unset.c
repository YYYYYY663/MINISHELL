/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymizukam <ymizukam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 19:48:35 by ymizukam          #+#    #+#             */
/*   Updated: 2025/01/04 22:08:06 by ymizukam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lmap.h"

/**
 * @brief 環境変数を削除する
 * 
 * この関数は以下の処理を行います：
 * 1. 指定されたキーに一致する環境変数を検索
 * 2. 一致した環境変数をリストから削除
 * 3. メモリを解放
 * 
 * @param key 削除する環境変数のキー
 * @param info シェル情報構造体
 * @return t_status 常にE_NONE（成功）を返す
 */
void	lmap_unset(char *key, t_lmap *lmap, int (*cmp)(void *,void *))
{
    if (!cmp)
        cmp = default_cmp;
	ft_list_remove_if(&lmap, key, cmp, free);
}
