/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _builtin_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymizukam <ymizukam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 22:08:25 by ymizukam          #+#    #+#             */
/*   Updated: 2025/01/14 17:20:58 by ymizukam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_builtin.h"
#include "ft_env.h"
#include "ft_system.h"
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

static int	_cd_home(char path[], char *arg, t_info *info);
static int	_cd_oldpwd(char path[], char *arg, t_info *info);
static int	_cd_cwd(char path[], char *arg, t_info *info);

/**
 * @brief カレントディレクトリを変更する（cdコマンド）
 *
 * この関数は以下の処理を行います：
 * 1. 引数の数をチェック
 *    - 引数がない場合：HOMEディレクトリに移動
 *    - 引数が'-'の場合：直前のディレクトリに移動
 *    - その他の引数：指定されたパスに移動
 * 2. 移動先のパスを解決
 * 3. ディレクトリを変更
 * 4. 環境変数PWDとOLDPWDを更新
 *
 * @param argv コマンド引数の配列（argv[0]はコマンド名）
 * @param info シェル情報構造体
 * @return t_status
 *    - E_NONE：正常終了
 *    - E_TOO_MANY_ARGS：引数が多すぎる
 *    - E_CHDIR：ディレクトリ変更失敗
 */
t_status	__cd(char **argv, t_info *info)
{
	char	absolute_path[PATH_MAX];

	if (argv[1] == NULL || argv[1][0] == '~')
	{
		if (_cd_home(absolute_path, argv[1], info))
			return (1);
	}
	else if (strncmp(argv[1], "-", 2) == 0)
	{
		if (_cd_oldpwd(absolute_path, argv[1], info))
			return (1);
	}
	else if (argv[1][0] == '.' || argv[1][0] == '/')
		path_dispacher(absolute_path, argv[1], F_OK, info);
	else
		_cd_cwd(absolute_path, argv[1], info);
	if (chdir(absolute_path) || access(absolute_path, F_OK))
		return (ft_dprintf(2, "cd: %s: %s\n", argv[1], strerror(errno)), 1);
	map_export_item("OLDPWD", info->cwd, info->env_map);
	ft_strlcpy(info->cwd, absolute_path, PATH_MAX);
	map_export_item("PWD", info->cwd, info->env_map);
	return (E_NONE);
}

/**
 * @brief HOMEディレクトリに移動する
 *
 * この関数は以下の処理を行います：
 * 1. HOME環境変数の値を取得
 * 2. 値が存在しない場合はエラー
 * 3. 取得したパスに移動
 *
 * @param path 移動先のパス
 * @param arg コマンド引数
 * @param info シェル情報構造体
 * @return int
 *    - 0：正常終了
 *    - 1：エラー
 */
static int	_cd_home(char path[], char *arg, t_info *info)
{
	char	*home;

	home = env_get("HOME", info);
	if (home[0] == '\0')
	{
		printf("cd: HOME not set\n");
		free(home);
		return (1);
	}
	free(home);
	if (arg == NULL)
		path_dispacher(path, "~", F_OK, info);
	else
		path_dispacher(path, arg, F_OK, info);
	return (0);
}

/**
 * @brief OLDPWDディレクトリに移動する
 *
 * この関数は以下の処理を行います：
 * 1. OLDPWD環境変数の値を取得
 * 2. 値が存在しない場合はエラー
 * 3. 取得したパスに移動
 *
 * @param path 移動先のパス
 * @param arg コマンド引数
 * @param info シェル情報構造体
 * @return int
 *    - 0：正常終了
 *    - 1：エラー
 */
static int	_cd_oldpwd(char path[], char *arg, t_info *info)
{
	char	*oldpwd;

	(void)arg;
	oldpwd = env_get("OLDPWD", info);
	if (oldpwd[0] == '\0')
	{
		ft_dprintf(2, "cd: OLDPWD not set\n");
		free(oldpwd);
		return (1);
	}
	path_dispacher(path, oldpwd, F_OK, info);
	free(oldpwd);
	return (0);
}

/**
 * @brief カレントディレクトリに相対パスを追加して移動する
 *
 * この関数は以下の処理を行います：
 * 1. カレントディレクトリのパスを取得
 * 2. 相対パスを追加
 *
 * @param path 移動先のパス
 * @param arg コマンド引数
 * @param info シェル情報構造体
 * @return int
 *    - 0：正常終了
 */
static int	_cd_cwd(char path[], char *arg, t_info *info)
{
	ft_strlcpy(path, info->cwd, PATH_MAX);
	ft_strlcat(path, "/", PATH_MAX);
	ft_strlcat(path, arg, PATH_MAX);
	return (0);
}
