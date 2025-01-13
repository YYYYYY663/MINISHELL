/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xalloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymizukam <ymizukam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 21:27:29 by teando            #+#    #+#             */
/*   Updated: 2025/01/05 03:36:30 by ymizukam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "system.h"

/**
 * @brief 失敗時に終了する安全なメモリ確保ラッパー関数
 * 
 * この関数は以下の処理を行います：
 * 1. 指定されたサイズのメモリ確保を試みる
 * 2. 確保したメモリをft_bzeroで0に初期化
 * 3. 確保に失敗した場合はプログラムを終了
 * 
 * @param size 確保するメモリのバイト数
 * @param info エラー処理用のシェルメイン情報構造体
 * @return void* 確保したメモリへのポインタ
 */
void	*xmalloc(size_t size, t_info *info)
{
	char	*memory;

	memory = malloc(size);
	if (!memory)
	{
		system_exit(info, E_ALLOCATE);
	}
	ft_bzero(memory, size);
	return ((void *)memory);
}

/**
 * @brief 失敗時に終了する安全な連結リストノード作成ラッパー関数
 * 
 * この関数は以下の処理を行います：
 * 1. 提供されたデータで新しいリストノードを作成
 * 2. ノード作成に失敗した場合はプログラムを終了
 * 
 * @param data 新しいノードに格納する文字列データ
 * @param info エラー処理用のシェルメイン情報構造体
 * @return t_list* 新しいリストノードへのポインタ
 */
t_list	*xlstnew(char *data, t_info *info)
{
	t_list	*list;

	list = ft_lstnew((void *)data);
	if (!list)
		system_exit(info, E_ALLOCATE);
	return (list);
}

// t_list	*xlst_from_strs(char **strs, t_info *info)
// {
// 	t_list	*list;

// 	list = ft_list_from_strs(strs);
// 	if (!list)
// 		system_exit(info, E_ALLOCATE);
// 	return (list);
// }

// char	**xlst_to_strs(t_list *lst, t_info *info)
// {
// 	char	**strs;

// 	strs = ft_list_to_strs(lst);
// 	if (!strs)
// 		system_exit(info, E_ALLOCATE);
// 	return (strs);
// }

// char	**xsplit(char *str, char sep, t_info *info)
// {
// 	char	**split;

// 	split = ft_split(str, sep);
// 	if (!split)
// 		system_exit(info, E_ALLOCATE);
// 	return (split);
// }
