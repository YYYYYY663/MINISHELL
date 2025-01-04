/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_new.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymizukam <ymizukam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 20:12:26 by ymizukam          #+#    #+#             */
/*   Updated: 2025/01/05 04:05:05 by ymizukam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_parser.h"
#include "ft_system.h"
#include "ft_token.h"

t_ast	*primary(t_list *list, t_info *info)
{
	t_ast	*node;

	while (consume(TT_LPAREN, &list))
	{
		node = expr(list, info);
		expect(TT_RPAREN, &list);
		return (node);
	}
	node = ast_node_new(NT_CMD, NULL, NULL);
	node->args = consume_args(&list);
	return (node);
}

t_ast	*pipeline(t_list *list, t_info *info)
{
	t_ast	*pipe_node;
	t_ast	*current_node;

	pipe_node = ast_node_new(NT_PIPE, primary(list, info), NULL);
	current_node = pipe_node;
	while (consume(TT_PIPE, &list))
	{
		current_node->right = ast_node_new(NT_PIPE, primary(list, info), NULL);
		current_node = current_node->right;
	}
	return (pipe_node);
}

t_ast	*expr(t_list *list, t_info *info)
{
	t_ast	*node;

	node = pipeline(list, info);
	while (1)
	{
		if (consume(TT_AND_AND, &list))
		{
			node = ast_node_new(NT_AND, node, pipeline(list, info));
		}
		else if (consume(TT_OR_OR, &list))
		{
			node = ast_node_new(NT_OR, node, pipeline(list, info));
		}
		else if (consume(TT_SEMICOLON, &list))
		{
			node = ast_node_new(NT_EOF, node, pipeline(list, info));
		}
		else
		{
			break ;
		}
	}
	return (node);
}
