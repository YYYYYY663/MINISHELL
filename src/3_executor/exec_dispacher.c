/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_dispacher.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymizukam <ymizukam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 16:24:35 by ymizukam          #+#    #+#             */
/*   Updated: 2024/12/22 16:28:04 by ymizukam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_executor.h"
#include "ft_system.h"

void	prefix_dispatcher(t_btree *current_node, t_info *info)
{
	const t_ast_node_item	*item = current_node->item;

	if (item->e_type == NT_PIPE)
	{
		setup_pipe(item->u_val.pipefds, info);
	}
}

void	suffix_dispatcher(t_btree *current_node, t_info *info)
{
	const t_ast_node_item	*item = current_node->item;

	if (item->e_type == NT_PIPE)
	{
		cleanup_pipe(item->u_val.pipefds, info);
	}
	if (item->e_type == NT_CMD)
	{
		process_cmd_node(item->u_val.argv, info);
	}
}

int	infix_dispatcher(t_btree *current_node, t_info *info)
{
	const t_ast_node_item	*item = current_node->item;

	if (item->e_type == NT_PIPE)
	{
		return (1);
	}
	// if (item->e_type == NT_CMD)
	// {
	// 	return (process_redir_node(item, info));
	// }
	return (0);
}
