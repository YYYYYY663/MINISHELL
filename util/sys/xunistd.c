/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xunistd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymizukam <ymizukam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 16:36:47 by ymizukam          #+#    #+#             */
/*   Updated: 2025/01/04 22:58:10 by ymizukam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sys.h"
#include "xunistd.h"

/**
 * @brief 失敗時に終了する安全なdup2システムコールラッパー関数
 * 
 * この関数は以下の処理を行います：
 * 1. fildesをfildes2に複製
 * 2. 元のファイルディスクリプタを閉じる
 * 3. dup2が失敗した場合はエラーステータスで終了
 * 
 * @param fildes 元のファイルディスクリプタ
 * @param fildes2 新しいファイルディスクリプタ
 * @param info エラー処理用のシェルメイン情報構造体
 */
void	xdup2(int fildes, int fildes2, t_info *info)
{
	if (dup2(fildes, fildes2) == -1)
	{
		perror("dup2");
		system_exit(info, errno);
	}
	xclose(&fildes);
}

/**
 * @brief 失敗時に終了する安全なforkシステムコールラッパー関数
 * 
 * この関数は以下の処理を行います：
 * 1. 新しいプロセスを作成
 * 2. fork失敗時はエラーステータスで終了
 * 
 * @param info エラー処理用のシェルメイン情報構造体
 * @return pid_t 親プロセスでは子プロセスのPID、子プロセスでは0
 */
pid_t	xfork(t_info *info)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		system_exit(info, errno);
	}
	return (pid);
}

/**
 * @brief 失敗時に終了する安全なpipeシステムコールラッパー関数
 * 
 * この関数は以下の処理を行います：
 * 1. 2つのファイルディスクリプタを持つパイプを作成
 * 2. パイプ作成失敗時はエラーステータスで終了
 * 
 * @param pipfds 読み書き用ファイルディスクリプタを格納する配列
 * @param info エラー処理用のシェルメイン情報構造体
 */
void	xpipe(int pipfds[], t_info *info)
{
	if (pipe(pipfds))
	{
		perror("pipe");
		system_exit(info, errno);
	}
}

/**
 * @brief メモリを解放してポインタをNULLにする安全なラッパー関数
 * 
 * この関数は以下の処理を行います：
 * 1. ポインタとその対象が有効かチェック
 * 2. 有効な場合はメモリを解放
 * 3. 解放後にポインタをNULLに設定
 * 
 * @param ptr 解放するポインタのポインタ
 */
void	xfree(void **ptr)
{
	if (!ptr || *ptr == NULL)
	{
		return ;
	}
	free(*ptr);
	*ptr = NULL;
}

/**
 * @brief 安全なcloseシステムコールラッパー関数
 * 
 * この関数は以下の処理を行います：
 * 1. ファイルディスクリプタの妥当性チェック（3以上であること）
 * 2. ファイルディスクリプタを閉じる
 * 3. クローズ後にfdを-1に設定
 * 4. close失敗時はエラーを報告
 * 
 * @param fd クローズするファイルディスクリプタへのポインタ
 * @return int 成功時は0、エラー時は-1
 */
int	xclose(int *fd)
{
	int	ret;

	if (!fd || *fd < 3)
	{
		return (0);
	}
	ret = close(*fd);
	if (ret == -1)
	{
		perror("close");
	}
	*fd = -1;
	return (ret);
}
