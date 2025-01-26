/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_dispatcher.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymizukam <ymizukam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 22:16:47 by ymizukam          #+#    #+#             */
/*   Updated: 2025/01/27 06:05:35 by ymizukam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_env.h"
#include "ft_lexer.h"
#include "ft_redirect.h"
#include "xunistd.h"
#include <string.h>

/**
 * @brief リダイレクトトークンを処理して適切なリダイレクトを設定する
 * 
 * この関数は以下の処理を行います：
 * 1. トークンリストを順番に処理
 * 2. トークンの種類に応じて適切なリダイレクトを実行：
 *    - TT_HEREDOC：ヒアドキュメント
 *    - TT_REDIR_IN：入力リダイレクト
 *    - TT_REDIR_OUT/TT_APPEND：出力リダイレクト
 * 3. エラー発生時：
 *    - エラーメッセージを表示
 *    - ファイルディスクリプタを閉じる
 *    - エラーステータスを返す
 * 
 * @param list リダイレクトトークンのリスト
 * @param in 標準入力のファイルディスクリプタ（更新される）
 * @param out 標準出力のファイルディスクリプタ（更新される）
 * @param info シェル情報構造体
 * @return t_status 成功時E_NONE、エラー時E_FILE
 */
t_status	redirect_dipatcher(t_list *list, int *in, int *out, t_info *info)
{
	t_token	*token;

	while (list != NULL)
	{
		token = list->data;
		if (token->type == TT_HEREDOC)
			heredoc(token->value, in, info);
		if (token->type == TT_REDIR_IN)
			redirect_in(token->type, token->value, in);
		if (token->type == TT_REDIR_OUT || token->type == TT_APPEND)
			redirect_out(token->type, token->value, out);
		if (*in == -1 || *out == -1)
		{
			ft_dprintf(2, "minishell: %s: %s\n", token->value, strerror(errno));
			xclose(out);
			xclose(in);
			return (E_FILE);
		}
		list = list->next;
	}
	return (E_NONE);
}
