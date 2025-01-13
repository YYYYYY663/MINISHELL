/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _builtin_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymizukam <ymizukam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 15:47:05 by teando            #+#    #+#             */
/*   Updated: 2025/01/05 02:40:26 by ymizukam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_builtin.h"
#include "ft_env.h"
#include "ft_system.h"

/**
 * @brief 環境変数の一覧を表示する（envコマンド）
 * 
 * この関数は以下の処理を行います：
 * 1. 環境変数リストを順番に走査
 * 2. 各環境変数エントリを標準出力に出力
 * 3. 各エントリの後に改行を出力
 * 
 * @param args コマンド引数（未使用）
 * @param info シェル情報構造体
 * @return t_status 常にE_NONE（成功）を返す
 */
t_status	__env(char **argv, t_info *info)
{
	char	**envp;

	envp = ft_list_to_strs(info->env_map);
	(void)argv;
	ft_putstrs_fd(envp, "\n", STDOUT_FILENO);
	ft_putendl_fd("", STDIN_FILENO);
	ft_strs_clear(envp);
	return (E_NONE);
}
