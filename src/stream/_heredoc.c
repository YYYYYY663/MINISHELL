/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _heredoc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymizukam <ymizukam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 22:17:00 by ymizukam          #+#    #+#             */
/*   Updated: 2025/01/05 21:54:45 by ymizukam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mish_stream.h"

/**
 * @brief ヒアドキュメントの入力を処理する
 * 
 * この関数は以下の処理を行います：
 * 1. パイプを作成して入力を受け付ける準備
 * 2. プロンプト（>）を表示して行入力を待機
 * 3. 入力された行をデリミタと比較：
 *    - 一致した場合：入力終了
 *    - 不一致の場合：パイプに書き込んで継続
 * 4. 終了時にパイプの書き込み側を閉じ、読み込み側を返す
 * 
 * 注意点：
 * - Ctrl+Dで入力を終了可能
 * - Ctrl+Cでシグナル処理
 * 
 * @param delimiter 終了を示すデリミタ文字列
 * @param in 標準入力のファイルディスクリプタ（更新される）
 * @param info シェル情報構造体
 */
void	heredoc(const char *delimiter, int *in, t_info *info)
{
	int		pipefds[2];
	char	*line;

	xclose(in);
	xpipe(pipefds, info);
	while (1)
	{
		printf(">");
		fflush(stdout);
		line = get_next_line(STDIN_FILENO);
		if (ft_strncmp(line, delimiter, ft_strlen(line) - 1) == 0)
		{
			free(line);
			break ;
		}
		write(pipefds[1], line, ft_strlen(line));
		free(line);
	}
	xclose(&pipefds[1]);
	*in = pipefds[0];
}
