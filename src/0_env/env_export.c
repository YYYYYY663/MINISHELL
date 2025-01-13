/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymizukam <ymizukam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 19:48:52 by ymizukam          #+#    #+#             */
/*   Updated: 2025/01/04 22:07:53 by ymizukam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_env.h"

/**
 * @brief 環境変数を設定する
 * 
 * この関数は以下の処理を行います：
 * 1. 環境変数のキーと値を分離
 * 2. キーの妥当性をチェック
 * 3. 既存の環境変数を検索：
 *    - 存在する場合は値を更新
 *    - 存在しない場合は新規作成
 * 
 * @param ent 環境変数エントリ（"KEY=VALUE"形式）
 * @param info シェル情報構造体
 * @return t_status 成功時E_NONE、失敗時エラーコード
 */
t_status	env_export(char *ent, t_info *info)
{
	char	key[PATH_MAX];
	char	*ent_cpy;
	int		delimiter;
	t_list	*lst;

	ent_cpy = ft_strdup(ent);
	if (ent_cpy == NULL)
		return (E_ALLOCATE);
	delimiter = ft_strcspn(ent, "=");
	ft_strlcpy(key, ent, delimiter + 1);
	if (_check_key(key))
		return (free(ent_cpy), E_ENV_KEY);
	lst = ft_list_find(info->env_map, key, __cmp);
	if (lst)
	{
		free(lst->data);
		lst->data = ent_cpy;
		return (E_NONE);
	}
	lst = ft_lstnew(ent_cpy);
	if (!lst)
		return (free(ent_cpy), E_ALLOCATE);
	ft_lstadd_back(&info->env_map, lst);
	return (E_NONE);
}

/**
 * @brief キーと値を指定して環境変数を設定する
 * 
 * この関数は以下の処理を行います：
 * 1. キーと値を"KEY=VALUE"形式に結合
 * 2. env_export関数を呼び出して設定
 * 
 * @param key 環境変数のキー
 * @param value 環境変数の値
 * @param info シェル情報構造体
 * @return t_status 成功時E_NONE、失敗時エラーコード
 */
t_status	env_export_item(char *key, char *value, t_info *info)
{
	char	ent[PATH_MAX];

	ft_strlcpy(ent, key, PATH_MAX);
	ft_strlcat(ent, "=", PATH_MAX);
	ft_strlcat(ent, value, PATH_MAX);
	return (env_export(ent, info));
}

// void map_append(t_info *info, char *key, char *val)
// {
// 	t_map *new = xmalloc(sizeof(t_map), info);
// 	new->key = key;
// 	new->val = val;
// 	lst = xlstnew(new, info);
// 	ft_lstadd_back(&info->env_map, lst);
// }

// t_status	env_export(t_info *info, char *key, char *val)
// {
// 	t_list	*lst;
// 	if (_check_key(info, key))
// 		xfree(&key);
// // 		return (free(ent_cpy), E_ENV_KEY);
// 	lst = ft_list_find(info->env_map, key, __cmp);
// 	if (lst) //すでに存在する場合上書き
// 	{
// 		xfree(&lst->data);
// 		lst->data = key;
// 		return (info->status);
// 	}
// 	map_append(info,key,val);
// 	// lst = ft_lstnew(ent_cpy);
// 	// ft_lstadd_back(&info->env_map, lst);
// 	return (E_NONE);
// }