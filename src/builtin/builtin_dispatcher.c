/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_dispatcher.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymizukam <ymizukam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 22:00:28 by teando            #+#    #+#             */
/*   Updated: 2025/01/14 12:33:34 by ymizukam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mish_builtin.h"

int	setup_builtin_args(t_args *args, int *in_fd, int *out_fd, t_info *info)
{
	if (redirect_dipacher(args->redr, in_fd, out_fd, info))
	{
		return (1);
	}
	info->stdfile_backup[0] = dup(STDIN_FILENO);
	info->stdfile_backup[1] = dup(STDOUT_FILENO);
	xdup2(*in_fd, STDIN_FILENO, info);
	xdup2(*out_fd, STDOUT_FILENO, info);
	args->cargv = convert_argv(args->argv);
	return (0);
}

/**
 * @brief ビルトインコマンドを識別して実行する
 *
 * この関数は以下の処理を行います：
 * 1. コマンド名が組み込みコマンドかチェック
 * 2. 組み込みコマンドの場合：
 *    - 対応する関数を呼び出す
 *    - 実行結果を返す
 * 3. 組み込みコマンドでない場合：
 *    - E_NOT_FOUND（未実装）を返す
 *
 * @param args コマンド引数の配列（args[0]はコマンド名）
 * @param in_fd 入力ファイルディスクリプタ
 * @param out_fd 出力ファイルディスクリプタ
 * @param info シェル情報構造体
 * @return t_status
 *    - E_NONE：正常終了
 *    - E_NOT_FOUND：コマンドが見つからない
 *    - その他：各ビルトインコマンドのエラーコード
 */
t_status	builtin_dispatcher(t_args *args, int *in_fd, int *out_fd,
		t_info *info)
{
	static const char		*builtin_names[] = {"pwd", "cd", "echo", "export",
				"unset", "exit", "env", "alias", "source"};
	static t_builtin_func	builtin_funcs[] = {__pwd, __cd, __echo, __export,
			__unset, __exit, __env, __alias, __source};
	size_t					i;
	t_token					*token;

	if (!args || !args->argv)
		return (E_NOT_BUITIN_CMD);
	token = (t_token *)args->argv->data;
	i = 0;
	if (*in_fd != 0 || *out_fd != 1 || token->value == NULL)
		return (E_NOT_BUITIN_CMD);
	while (i < sizeof(builtin_names) / sizeof(builtin_names[0]))
	{
		if (ft_strcmp(token->value, builtin_names[i]) == 0)
		{
			if (setup_builtin_args(args, in_fd, out_fd, info))
				return (E_FILE);
			info->status = builtin_funcs[i](args->cargv, info);
			xdup2(info->stdfile_backup[0], STDIN_FILENO, info);
			xdup2(info->stdfile_backup[1], STDOUT_FILENO, info);
			return (info->status);
		}
		i++;
	}
	return (E_NOT_BUITIN_CMD);
}
