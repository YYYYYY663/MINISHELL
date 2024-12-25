/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_root_new.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymizukam <ymizukam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 20:12:26 by ymizukam          #+#    #+#             */
/*   Updated: 2024/12/24 20:38:08 by ymizukam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_system.h"
#include "ft_token.h"
#include "xunistd.h"

t_ast	*ast_node_new(int type, t_list *args, t_info *info)
{
	t_ast	*new_node;

	new_node = xmalloc(sizeof(t_ast), info);
	new_node->e_type = type;
	new_node->args = args;
	return (new_node);
}
t_list	*consume_token(t_token_type type, t_list **lst)
{
	t_list	*args;
	t_token *token = (t_token *)(*lst)->data;
	while (token->type != type)
	{
		
	}
}

// WORDが来たら
t_ast	*ast_pipe_new(t_list *list, t_info *info)
{
	t_ast	*pipe_node;
	t_ast	*current_node;
	t_token *token = (t_token *)list->data;

	pipe_node = astnew_node(NT_PIPE, NULL, info);
	current_node = pipe_node;
	while (list != NULL)
	{
		current_node->left = astnew_node(NT_CMD, consume_token(TT_WORD, &list),
				info);
		if (list)
			current_node->right = astnew_node(NT_PIPE, NULL, info);
		current_node = current_node->right;
	}
	return (pipe_node);
}



// t_ast	*astnew_node(int type, char *argv, t_info *info)
// {
// 	t_ast	*new_node;

// 	new_node = xmalloc(sizeof(t_ast), info);
// 	new_node->type = type;
// 	new_node->args = ft_split(argv, ' ');
// 	return (new_node);
// }

// t_ast	*ast_new(char **argv, t_info *info)
// {
// 	t_ast	*root_node;
// 	t_ast	*current_node;

// 	root_node = astnew_node(TOKEN_PIPE, NULL, info);
// 	current_node = root_node;
// 	while (*argv != NULL)
// 	{
// 		current_node->left = astnew_node(TOKEN_CMD, *argv++, info);
// 		if (*argv)
// 			current_node->right = astnew_node(TOKEN_PIPE, NULL, info);
// 		current_node = current_node->right;
// 	}
// 	return (root_node);
// }