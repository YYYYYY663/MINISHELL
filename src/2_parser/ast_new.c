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
# include "ft_parser.h"


t_args *ast_args_new(t_info *info)
{
    (void)info;
    t_args *args = ft_calloc(1, sizeof(t_args));
    args->fds[0] = -1;
    args->fds[1] = -1;
    args->pid = -1;

    return args;
}

t_ast	*ast_node_new(int type, t_ast *left, t_ast *right, t_info *info)
{

	t_ast	*node;
    (void)info;
	//new_node = xmalloc(sizeof(t_ast), info);
    node = ft_calloc(1,sizeof(t_ast));
	node->ntype = type;
	node->left = left;
	node->right = right;
	return (node);
}

t_args	*consume_args(t_list **lst, t_info *info)
{
	t_args	*args = ast_args_new(info);
    t_list *new_lst;
	t_token *token = (t_token *)(*lst)->data;
    #ifdef FUNC_OUT
		printf("%s node: %s\n",__func__,type_to_str(token->type));
	#endif
	while ((token->type & 0xF000) == CMD_ARG)
	{
        new_lst = ft_lstnew(token->value);
        if (token->type == TT_WORD)
		    ft_lstadd_back(&args->argv, new_lst);
        if (token->type == TT_HEREDOC || token->type == TT_REDIR_IN)
            ft_lstadd_back(&args->redr, new_lst);
        if (token->type == TT_APPEND || token->type == TT_REDIR_OUT)
            ft_lstadd_back(&args->redr, new_lst);
        (*lst)->data = NULL;
        (*lst) = (*lst)->next;
        token = (t_token *)(*lst)->data;
	}
    return args;
}


// 次のトークンが期待している記号のときには、トークンを1つ読み進めて
// 真を返す。それ以外の場合には偽を返す。
int	consume(t_token_type type, t_list **lst)
{
	t_token *token = (t_token *)(*lst)->data;
	if (type != token->type)
		return 0;
	*lst = (*lst)->next;	
	return 1;
}
// 次のトークンが期待している記号のときには、トークンを1つ読み進める。
// それ以外の場合にはエラーを報告する。
void expect(t_token_type type, t_list **lst) 
{
	t_token *token = (t_token *)(*lst)->data;
	if (type != token->type)
	{
		printf("expected %d", type);
		// system_exit()
	}
	*lst = (*lst)->next;	
}

t_ast *primary(t_list **list, t_info *info)
{
	#ifdef FUNC_OUT
		t_token *token = (t_token *)(*list)->data;
		printf("%s node: %s\n",__func__,type_to_str(token->type));
	#endif
	t_ast *node;
	while (consume(TT_LPAREN,list))
	{
		node = expr(list,info);
		expect(TT_RPAREN,list);
		return node;
	}
	node = ast_node_new(NT_CMD ,NULL, NULL, info);
    node->args = consume_args(list,info);
	return node;
}

// WORDが来たら 
// todo (がさきに来た時の対策も
//最初に|, && ||がきたらsyntax error
t_ast	*pipeline(t_list **list, t_info *info)
{
	t_ast	*pipe_node;
	t_ast	*current_node;
    #ifdef FUNC_OUT
		t_token *token = (t_token *)(*list)->data;
		printf("%s node: %s\n",__func__,type_to_str(token->type));
	#endif
	pipe_node = ast_node_new(NT_PIPE, primary(list,info), NULL ,info);
	current_node = pipe_node;
	while (consume(TT_PIPE, list))
	{
		current_node->right = ast_node_new(NT_PIPE, primary(list,info) ,NULL, info);
		current_node = current_node->right;
	}
	return (pipe_node);
}



t_ast	*expr(t_list **list, t_info *info)
{
	t_ast	*node = pipeline(list, info);
	
	while (1)
	{
		if (consume(TT_AND_AND,list))
		{
			node = ast_node_new(NT_AND, node, pipeline(list,info),info);
		}
		else if (consume(TT_OR_OR,list))
		{
			node = ast_node_new(NT_OR, node, pipeline(list,info),info);
		}
		else if (consume(TT_SEMICOLON,list))
		{
			node = ast_node_new(NT_EOF, node, pipeline(list,info),info);
		}
		else
		{
			break;
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
//       return node;
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
//       return node;
//   }
// }
// Node *primary() {
//   // 次のトークンが"("なら、"(" expr ")"のはず
//   if (consume('(')) {
//     Node *node = expr();
//     expect(')');
//     return node;
//   }

//   // そうでなければ数値のはず
//   return new_node_num(expect_number());
// }