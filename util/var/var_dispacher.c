/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_dispacher.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymizukam <ymizukam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 17:12:59 by ymizukam          #+#    #+#             */
/*   Updated: 2025/01/05 21:57:43 by ymizukam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "variable.h"

/**
 * @brief 変数展開を制御する
 * 
 * この関数は以下の処理を行います：
 * 1. トークンリストを順番に処理
 * 2. 各トークンに対して：
 *    - アスタリスク（*）によるグロブ展開
 *      - ダブルクォート内では展開しない
 *    - ドル記号（$）による環境変数展開
 *      - シングルクォート内では展開しない
 *      - ダブルクォート内では単語分割しない
 * 
 * @param lst トークンリストのヘッド
 * @param info シェル情報構造体
 * @return int 0:成功、-1:失敗
 */
int	var_dispacher(t_list **lst, t_info *info)
{
	t_list	*head;
	t_token	*token;

	head = *lst;
	token = (t_token *)head->data;
	(void)info;
	while (head->next)
	{
		if (ft_strchr(token->value, '*'))
		{
            
			// expand_astarisk(&head, info);
			// DOUBLE QUOTE noexpand
		}
		if (ft_strchr(token->value, '$'))
		{
			// expand_dollar(&head, info);
			// SINGLE QUOTE no expand
			// DOUBLE QUOTE no word split
		}
		// head may change
		token = (t_token *)head->data;
		if (ft_strchr(token->value, '$') == NULL)
		{
			head = head->next;
			token = (t_token *)head->data;
		}
	}
	return (0);
}
