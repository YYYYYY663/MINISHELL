/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_new.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymizukam <ymizukam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 20:12:26 by ymizukam          #+#    #+#             */
/*   Updated: 2025/01/04 22:50:28 by ymizukam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_parser.h"
#include "ft_system.h"
#include "ft_token.h"

t_ast	*primary(t_list **list, t_info *info)
{
	t_ast	*node;

#ifdef FUNC_OUT
	token = (t_token *)(*list)->data;
	printf("%s node: %s\n", __func__, type_to_str(token->type));
#endif
	while (consume(TT_LPAREN, list))
	{
		node = expr(list, info);
		expect(TT_RPAREN, list);
		return (node);
	}
	node = ast_node_new(NT_CMD, NULL, NULL, info);
	node->args = consume_args(list, info);
	return (node);
}

// WORDが来たら
// todo (がさきに来た時の対策も
//最初に|, && ||がきたらsyntax error
t_ast	*pipeline(t_list **list, t_info *info)
{
	t_ast	*pipe_node;
	t_ast	*current_node;

#ifdef FUNC_OUT
	token = (t_token *)(*list)->data;
	printf("%s node: %s\n", __func__, type_to_str(token->type));
#endif
	pipe_node = ast_node_new(NT_PIPE, primary(list, info), NULL, info);
	current_node = pipe_node;
	while (consume(TT_PIPE, list))
	{
		current_node->right = ast_node_new(NT_PIPE, primary(list, info), NULL,
				info);
		current_node = current_node->right;
	}
	return (pipe_node);
}

t_ast	*expr(t_list **list, t_info *info)
{
	t_ast	*node;

	node = pipeline(list, info);
	while (1)
	{
		if (consume(TT_AND_AND, list))
		{
			node = ast_node_new(NT_AND, node, pipeline(list, info), info);
		}
		else if (consume(TT_OR_OR, list))
		{
			node = ast_node_new(NT_OR, node, pipeline(list, info), info);
		}
		else if (consume(TT_SEMICOLON, list))
		{
			node = ast_node_new(NT_EOF, node, pipeline(list, info), info);
		}
		else
		{
			break ;
		}
	}
	return (node);
}

// Node *expr() {
//   Node *node = mul();

//   for (;;) {
//     if (consume('+'))
//       node = new_node(ND_ADD, node, mul());
//     else if (consume('-'))
//       node = new_node(ND_SUB, node, mul());
//     else
//       return (node);
//   }
// }
// Node *mul() { pipeline
//   Node *node = primary();

//   for (;;) {
//     if (consume('*'))
//       node = new_node(ND_MUL, node, primary());
//     else if (consume('/'))
//       node = new_node(ND_DIV, node, primary());
//     else
//       return (node);
//   }
// }
// Node *primary() {
//   // 次のトークンが"("なら、"(" expr ")"のはず
//   if (consume('(')) {
//     Node *node = expr();
//     expect(')');
//     return (node);
//   }

//   // そうでなければ数値のはず
//   return (new_node_num(expect_number()));
// }