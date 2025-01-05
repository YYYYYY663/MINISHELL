/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _ast_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymizukam <ymizukam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 02:46:04 by ymizukam          #+#    #+#             */
/*   Updated: 2025/01/05 21:54:20 by ymizukam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_executor.h"
#include "ft_parser.h"
#include "ft_system.h"
#include "ft_token.h"

t_status	exec_pipeline(t_ast *node, t_info *info)
{
	if (node->left->ntype == NT_CMD)
		return (pipe_node(node, STDIN_FILENO, STDOUT_FILENO, info));
	else
		return (traverse_ast_nodes(node->left, info));
}

void	kill_pipeline(t_ast *node, t_info *info)
{
	(void)info;
	if (node == NULL)
		return ;
	kill_pipeline(node->right, info);
	if (node->ntype == NT_CMD)
	{
		xclose(&node->args->fds[0]);
		xclose(&node->args->fds[1]);
		if (node->args->pid != -1)
			waitpid(node->args->pid, NULL, 0);
		node->args->pid = -1;
	}
	kill_pipeline(node->left, info);
}

// if (node->args->pid != -1)
// 	kill(node->args->pid, SIGTERM);