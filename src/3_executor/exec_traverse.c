/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_traverse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymizukam <ymizukam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 16:28:15 by ymizukam          #+#    #+#             */
/*   Updated: 2024/12/22 16:55:08 by ymizukam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_executor.h"
#include "ft_system.h"
#include "ft_token.h"
#include "ft_parser.h"
/*
 * CMDの処理はpreでもinでもどこでも大丈夫
 * signal handlingのためにすべてにifcheckをいれるべき
 */
int g_signal = 0;


t_status exec_pipe_node(t_ast *node, t_info *info)
{
	return E_NONE;
}


t_status	traverse_ast_nodes(t_ast *node, t_info *info)
{
	t_status status;
	if (node == NULL)
		return (E_NONE);
	if (g_signal)
		return ((t_status)g_signal);
	#ifdef FUNC_OUT
		printf("%s node: %s\n",__func__, e_type_to_str(node->ntype));
	#endif
	
	// if (node->ntype == NT_CMD)pipeの中で処理する

	if (node->ntype == NT_PIPE)
		return exec_pipe_node(node, info);
	
	if (node->ntype == NT_AND)
	{
		status = traverse_ast_nodes(node->left, info);
		if (!status)
			return(traverse_ast_nodes(node->right, info));

	}
	if (node->ntype == NT_OR)
	{
		status = traverse_ast_nodes(node->left, info);
		if (status)
			return(traverse_ast_nodes(node->right, info));
	}

	if (node->ntype == NT_EOF)
	{
		status = traverse_ast_nodes(node->left, info);
		status = traverse_ast_nodes(node->right, info);
	}

	return status;
}