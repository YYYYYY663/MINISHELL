/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _exec_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymizukam <ymizukam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 22:17:47 by ymizukam          #+#    #+#             */
/*   Updated: 2025/01/05 21:54:32 by ymizukam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_env.h"
#include "ft_executor.h"
#include "ft_parser.h"
#include "ft_redirect.h"
#include "ft_system.h"


/**
 * @brief コマンド実行の準備を行う
 * 
 * この関数は以下の処理を行います：
 * 1. リダイレクトの設定を適用
 * 2. コマンドの存在確認とパスの解決
 * 3. 引数リストの変換（t_list -> char**）
 * 4. ファイルディスクリプタの設定
 * 
 * エラー発生時：
 * - リダイレクトエラー：ステータスを1に設定
 * - コマンドが見つからない：ステータスを127に設定
 * 
 * @param args コマンド引数構造体
 * @param in_fd 標準入力のファイルディスクリプタ
 * @param out_fd 標準出力のファイルディスクリプタ
 * @param info シェル情報構造体
 * @return int 成功時0、エラー時1
 */
int	setup_args(t_args *args, int *in_fd, int *out_fd, t_info *info)
{
	t_token	*token;

	if (redirect_dipacher(args->redr, in_fd, out_fd, info))
	{
		info->status = 1;
		return (1);
	}
	token = (t_token *)args->argv->data;
	if (token->value == NULL)
	{
		return (1);
	}
	if (path_dispacher(args->path, token->value, X_OK, info))
	{
		ft_dprintf(2, "minishell: %s: command not found\n", token->value);
		info->status = 127;
		return (1);
	}
	args->cargv = convert_argv(args->argv);
	args->fds[0] = *in_fd;
	args->fds[1] = *out_fd;
	return (0);
}
