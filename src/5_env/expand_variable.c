/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _var_expand_dollar.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymizukam <ymizukam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 17:18:58 by ymizukam          #+#    #+#             */
/*   Updated: 2025/01/15 19:56:15 by ymizukam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_env.h"
#include "ft_lexer.h"
#include "ft_system.h"
#include "xunistd.h"

// ft_strjoin_freeのプロトタイプ宣言を追加
// char *ft_strjoin_free(char *s1, char *s2, int mode);

/**
 * @brief 環境変数の再帰的な展開を行う
 *
 * この関数は以下の処理を行います：
 * 1. 環境変数の値を取得
 * 2. 取得した値が別の環境変数を参照している場合は再帰的に展開
 * 3. 最終的な値を返す
 *
 * @param var 展開する環境変数名
 * @param info シェル情報構造体
 * @return char* 展開された値（メモリ確保済み）
 */
// static char	*resolve_recursive_env(const char *var, t_info *info)
// {
// 	char	*cur;
// 	char	*val;
// 	char	*tmp;
// 	char	*check_next;

// 	cur = ft_strdup(var);
// 	val = NULL;
// 	while (1)
// 	{
// 		tmp = env_get(cur, info);
// 		free(cur);
// 		if (!tmp || !*tmp)
// 		{
// 			if (tmp)
// 				free(tmp);
// 			val = ft_strdup("");
// 			break ;
// 		}
// 		check_next = env_get(tmp, info);
// 		if (!check_next || !*check_next)
// 		{
// 			if (check_next)
// 				free(check_next);
// 			val = tmp;
// 			break ;
// 		}
// 		free(tmp);
// 		cur = check_next;
// 	}
// 	return (val);
// }

/**
 * @brief $記号による環境変数展開を行う
 *
 * この関数は以下の処理を行います：
 * 1. トークン内の$記号を検索
 * 2. $記号以降の環境変数名を抽出
 * 3. 環境変数を展開して置換
 * 4. 複数の環境変数が存在する場合は全て展開
 *
 * @param head トークンリストのヘッド
 * @param info シェル情報構造体
 * @return int 0:成功、-1:失敗
 */
// int	expand_dollar(t_list **head, t_info *info)
// {
// 	t_token	*token;
// 	char	*str;
// 	size_t	i;
// 	char	*expanded;
// 	char	*varname;
// 		size_t start;
// 		char *val;

// 	token = (t_token *)(*head)->data;
// 	str = token->value;
// 	i = 0;
// 	expanded = ft_calloc(1, 1);
// 	while (str[i])
// 	{
// 		start = i;
// 		while (str[i] && str[i] != '$')
// 			i++;
// 		expanded = ft_strjoin_free(expanded, ft_substr(str, start, i - start),
// 				3);
// 		if (str[i] == '$')
// 		{
// 			i++;
// 			start = i;
// 			while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
// 				i++;
// 			varname = ft_substr(str, start, i - start);
// 			val = resolve_recursive_env(varname, info);
// 			free(varname);
// 			expanded = ft_strjoin_free(expanded, val, 1);
// 		}
// 	}
// 	free(token->value);
// 	token->value = expanded;
// 	return (0);
// }
