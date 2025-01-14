/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _builtin_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymizukam <ymizukam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 22:06:41 by ymizukam          #+#    #+#             */
/*   Updated: 2025/01/14 12:54:22 by ymizukam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mish_builtin.h"

static void	_swap(char **a, char **b);
static void	_display_sorted_env(t_info *info);
static void	_display_sorted_env_line(const char *entity);

// int	default_check(char *key)
// {
// 	int	i;

// 	if (!ft_isalpha(key[0]) && key[0] != '_')
// 	{
// 		ft_dprintf(STDERR_FILENO,
// 			"minishell: export: `%s\': not a valid identifier\n", key);
// 		return (1);
// 	}
// 	i = 0;
// 	while (key[++i])
// 	{
// 		if (!ft_isalnum(key[i]) && key[i] != '_')
// 		{
// 			ft_dprintf(STDERR_FILENO,
// 				"minishell: export: `%s\': not a valid identifier\n", key);
// 			return (1);
// 		}
// 	}
// 	return (0);
// }
t_status	__export(char **argv, t_info *info)
{
	int		i;
	char	*key;
	char	*value;

	i = 0;
	if (!argv[1])
	{
		_display_sorted_env(info);
	}
	while (argv[++i])
	{
		key = ft_substr_l(argv[i], '='); // todo validation
		value = ft_substr_r(argv[i], '=');
		lmap_export(key, value, info->env_map, NULL);
		free(key);
		free(value);
	}
	return (E_NONE);
}

static void	_swap(char **a, char **b)
{
	char	*tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

/**
 * @brief 環境変数をソートして表示する
 *
 * この関数は以下の処理を行います：
 * 1. 環境変数リストを配列に変換
 * 2. 配列をソート
 * 3. 各環境変数を"declare -x KEY=VALUE"形式で表示
 * 4. メモリを解放
 *
 * @param info シェル情報構造体
 * @return t_status
 *    - E_NONE：正常終了
 *    - E_ALLOCATE：メモリ割り当て失敗
 */
static void	_display_sorted_env(t_info *info)
{
	char	**envp;
	int		len;
	int		i;
	int		j;

	envp = ft_list_to_strs(info->env_map);
	len = ft_list_size(info->env_map);
	i = 0;
	while (i < len - 1)
	{
		j = i + 1;
		while (j < len)
		{
			if (ft_strcmp(envp[i], envp[j]) > 0)
			{
				_swap(&envp[i], &envp[j]);
			}
			j++;
		}
		_display_sorted_env_line(envp[i++]);
	}
	_display_sorted_env_line(envp[i]);
}

static void	_display_sorted_env_line(const char *entity)
{
	char	*key;
	char	*value;

	key = ft_substr_l(entity, '=');
	value = ft_substr_r(entity, '=');
	ft_putstr_fd("declare -x ", STDOUT_FILENO);
	ft_putstr_fd(key, STDOUT_FILENO);
	if (value[0])
	{
		ft_putstr_fd("=\"", STDOUT_FILENO);
		ft_putstr_fd(value, STDOUT_FILENO);
		ft_putstr_fd("\"", STDOUT_FILENO);
	}
	printf("\n");
	free(value);
	free(key);
}
