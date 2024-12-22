/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_traverse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymizukam <ymizukam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 16:28:15 by ymizukam          #+#    #+#             */
/*   Updated: 2024/12/22 16:31:40 by ymizukam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_executor.h"
#include "ft_system.h"

/*
 * CMDの処理はpreでもinでもどこでも大丈夫
 * signal handlingのためにすべてにifcheckをいれるべき
 */
t_status	traverse_ast_nodes(t_btree *current_node, t_info *info)
{
	if (current_node == NULL)
		return (0);
	// プリフィックス処理
	prefix_dispatcher(current_node, info); // pipeの準備
	// 左部分木を処理
	traverse_ast_nodes(current_node->left, info);
	// インフィックス処理
	if (infix_dispatcher(current_node, info))
		return (info->status); //&&, || などの処理
	// 右部分木を処理
	traverse_ast_nodes(current_node->right, info);
	// サフィックス処理
	suffix_dispatcher(current_node, info); // pipeのクローズなど
	return (info->status);
}