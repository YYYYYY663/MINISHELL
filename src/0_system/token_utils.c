/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymizukam <ymizukam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 22:15:51 by ymizukam          #+#    #+#             */
/*   Updated: 2025/01/05 21:58:02 by ymizukam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_system.h"
#include "ft_token.h"
#include "xunistd.h"

/**
 * @brief トークンの連結リストを文字列配列（argv形式）に変換する
 * 
 * この関数は以下の処理を行います：
 * 1. トークン値からNULL終端の文字列配列を作成
 * 2. 配列と各文字列用のメモリを確保
 * 3. エラー発生時は確保したメモリを適切に解放
 * 
 * @param lst t_token構造体の連結リスト
 * @return char** 文字列配列（argv形式）、エラー時はNULL
 */
char	**convert_argv(t_list *lst)
{
	char	**cargv;
	t_token	*token;
	size_t	i;

	if (!lst || !lst->data)
		return (NULL);
	cargv = ft_calloc(ft_lstsize(lst) + 1, sizeof(char *));
	if (!cargv)
		return (NULL);
	i = 0;
	while (lst)
	{
		token = lst->data;
		if (!token || !token->value)
			return (ft_strs_clear(cargv), NULL);
		cargv[i] = ft_strdup(token->value);
		if (!cargv[i])
			return (ft_strs_clear(cargv), NULL);
		i++;
		lst = lst->next;
	}
	cargv[i] = NULL;
	return (cargv);
}

/**
 * @brief トークン構造体に関連する全てのメモリを解放する
 * 
 * この関数は以下の処理を行います：
 * 1. トークンの値文字列が存在する場合は解放
 * 2. トークン構造体自体を解放
 * トークンリスト操作のクリーンアップ関数として使用
 * 
 * @param ptr 解放するトークン構造体へのポインタ（互換性のためvoid*）
 */
void	token_clear(void *ptr)
{
	t_token	*token;

	token = (t_token *)ptr;
	if (token == NULL)
		return ;
	if (token->value)
		free(token->value);
	free(token);
}
