/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _builtin_echo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymizukam <ymizukam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 15:48:32 by teando            #+#    #+#             */
/*   Updated: 2025/01/05 02:40:18 by ymizukam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mish_builtin.h"

static int	_validate_option(char *arg);

/**
 * @brief 引数を標準出力に出力する（echoコマンド）
 * 
 * この関数は以下の処理を行います：
 * 1. -nオプションの有無をチェック
 *    - -nオプション：最後の改行を出力しない
 * 2. 引数を順番に出力
 *    - 引数と引数の間にスペースを挿入
 *    - -nオプションがない場合は最後に改行を出力
 * 
 * @param args コマンド引数の配列（args[0]はコマンド名）
 * @param info シェル情報構造体
 * @return t_status 常にE_NONE（成功）を返す
 */
t_status	__echo(char **argv, t_info *info)
{
	int	is_option_n;
	int	is_first;

	is_option_n = 0;
	is_first = 1;
	(void)info;
	while (*++argv)
	{
		if (_validate_option(*argv))
		{
			is_option_n = 1;
			continue ;
		}
		if (!is_first)
			ft_putchar_fd(' ', STDOUT_FILENO);
		is_first = 0;
		ft_putstr_fd(*argv, STDOUT_FILENO);
	}
	if (!is_option_n)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (E_NONE);
}

static int	_validate_option(char *arg)
{
	if (arg[0] != '-' || arg[1] == '\0')
		return (0);
	while (arg[1])
	{
		if (arg[1] != 'n')
			return (0);
		arg++;
	}
	return (1);
}
