/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _builtin_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymizukam <ymizukam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 15:45:58 by teando            #+#    #+#             */
/*   Updated: 2025/01/05 21:52:49 by ymizukam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_builtin.h"
#include "ft_env.h"
#include "ft_system.h"

/**
 * @brief シェルを終了する（exitコマンド）
 * 
 * この関数は以下の処理を行います：
 * 1. 引数の数をチェック
 *    - 引数が多すぎる場合はエラー
 * 2. 終了ステータスの処理：
 *    - 引数がある場合：数値として解析
 *    - 数値以外の場合はエラー
 *    - 引数がない場合：直前のコマンドの終了ステータスを使用
 * 3. シェルを終了
 * 
 * @param argv コマンド引数の配列（argv[0]はコマンド名）
 * @param info シェル情報構造体
 * @return t_status 
 *    - E_TOO_MANY_ARGS：引数が多すぎる
 *    - E_INVALID_ARG：無効な引数
 *    - E_NONE：正常終了（実際には到達しない）
 */
t_status	__exit(char **argv, t_info *info)
{
	long	exit_status;
	char	*endptr;

	exit_status = 0;
	ft_dprintf(1, "exit\n");
	if (argv[1] != NULL)
	{
		exit_status = ft_strtol(argv[1], &endptr, 10);
		if (endptr != argv[1] + ft_strlen(argv[1]) || exit_status > INT_MAX
			|| exit_status < INT_MIN)
		{
			ft_dprintf(2, "minishell: exit: %s: numeric argument required\n",
				argv[1]);
			system_exit(info, 2);
		}
		else if (argv[2])
		{
			ft_putstr_fd("minishell: exit: too many arguments\n",
				STDERR_FILENO);
			return (1);
		}
	}
	system_exit(info, (t_status)exit_status % 0x100);
	return (1);
}
