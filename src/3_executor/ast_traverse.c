/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_traverse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymizukam <ymizukam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 16:28:15 by ymizukam          #+#    #+#             */
/*   Updated: 2025/01/05 22:03:34 by ymizukam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_executor.h"
#include "ft_parser.h"
#include "ft_system.h"
#include "ft_token.h"

int			g_signal = 0;

t_status	exec_connector(t_ast *node, t_info *info)
{
	if (node->ntype == NT_AND)
	{
		traverse_ast_nodes(node->left, info);
		if (!info->status)
			return (traverse_ast_nodes(node->right, info));
	}
	else if (node->ntype == NT_OR)
	{
		traverse_ast_nodes(node->left, info);
		if (info->status)
			return (traverse_ast_nodes(node->right, info));
	}
	else if (node->ntype == NT_EOF)
	{
		traverse_ast_nodes(node->left, info);
		traverse_ast_nodes(node->right, info);
	}
	return (E_NONE);
}

t_status	traverse_ast_nodes(t_ast *node, t_info *info)
{
	if (node == NULL)
		return (E_NONE);
	if (g_signal)
		return ((t_status)g_signal);
	if (node->ntype == NT_PIPE)
	{
		exec_pipeline(node, info);
		kill_pipeline(node, info);
#ifndef DEBUGOFF
		printf("status %d\n", info->status);
#endif
		free(info->env_spc['?']);
		info->env_spc['?'] = ft_itoa(info->status);
		return (E_NONE);
	}
	return (exec_connector(node, info));
}
