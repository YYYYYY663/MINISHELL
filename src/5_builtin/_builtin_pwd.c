/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _builtin_pwd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymizukam <ymizukam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 22:12:58 by ymizukam          #+#    #+#             */
/*   Updated: 2025/01/05 02:42:18 by ymizukam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_builtin.h"
#include "ft_env.h"
#include "ft_system.h"

/*
 *ref char * getcwd(char *buf, size_t size);
 */

/**
 * @brief カレントディレクトリのパスを表示する（pwdコマンド）
 * 
 * この関数は以下の処理を行います：
 * 1. シェル情報構造体からカレントディレクトリのパスを取得
 * 2. パスを標準出力に出力
 * 3. 改行を出力
 * 
 * @param args コマンド引数（未使用）
 * @param info シェル情報構造体
 * @return t_status 常にE_NONE（成功）を返す
 */
t_status	__pwd(char **argv, t_info *info)
{
	(void)argv;
	printf("%s\n", info->cwd);
	return (E_NONE);
}
