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
	t_token *token = (t_token *)(*lst)->data;
    t_list *new_lst;
    #ifdef FUNC_OUT
		printf("%s node: %s\n",__func__,type_to_str(token->type));
	#endif
	while ((token->type & 0xF000) == CMD_ARG)
	{
        printf("consume %s\n", token->value);
        new_lst = ft_lstnew(token->value);
        if (token->type == TT_WORD)
		    ft_lstadd_back(&args->cmd, new_lst);
        if (token->type == TT_HEREDOC || token->type == TT_REDIR_IN)
            ft_lstadd_back(&args->rd_i, new_lst);
        if (token->type == TT_APPEND || token->type == TT_REDIR_OUT)
            ft_lstadd_back(&args->rd_o, new_lst);
        (*lst)->data = NULL;
        (*lst) = (*lst)->next;
        token = (t_token *)(*lst)->data;
	}
    return args;
}




t_ast *primary(t_list **list, t_info *info)
{
	t_token *token = (t_token *)(*list)->data;
	#ifdef FUNC_OUT
		printf("%s node: %s\n",__func__,type_to_str(token->type));
	#endif
	t_ast *node;
	if (token->type == TT_LPAREN)
	{
		*list = (*list)->next;
		expr(list,info);
		token = (t_token *)(*list)->data;
		if (token->type != TT_RPAREN)
		{
			printf("paren doesn't macth\n");
		}
	}
	node = ast_node_new(NT_CMD ,NULL, NULL, info);
	//leftにargsを加えていく
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
	t_token *token = (t_token *)(*list)->data;
    #ifdef FUNC_OUT
		printf("%s node: %s\n",__func__,type_to_str(token->type));
	#endif

	pipe_node = primary(list, info);
	//pipe_node = ast_node_new(NT_PIPE, NULL,NULL ,info);
	current_node = pipe_node;
	while (1)//まず読むのはWORD REDIRのどれか
	{
		// current_node->left = ast_node_new(NT_CMD ,NULL, NULL, info);
        // //leftにargsを加えていく
        // current_node->left->args = consume_args(&list,info);
		//leftにargsを加えていく
        //current_node->left = primary(list,info);
        token = (t_token *)(*list)->data;
        if (token->type != TT_PIPE)
            break;
		current_node->right = ast_node_new(NT_PIPE,NULL,NULL, info);
        *list = (*list)->next;
		current_node = current_node->right;
	}
    //pipe以外のものがきたら抜ける（bonus)
	return (pipe_node);
}



t_ast	*expr(t_list **list, t_info *info)
{
	t_token *token;
	token = (t_token *)(*list)->data;
	#ifdef FUNC_OUT
		printf("%s node: %s\n",__func__,type_to_str(token->type));
	#endif
	t_ast	*node = pipeline(list, info);
	token = (t_token *)(*list)->data;
	while (1)
	{
		if (token->type == TT_AND_AND)
		{
			*list = (*list)->next;
			node = ast_node_new(NT_AND, node, pipeline(list,info),info);
		}
		else if (token->type == TT_OR_OR)
		{
			*list = (*list)->next;
			node = ast_node_new(NT_OR, node, pipeline(list,info),info);
		}
		else if (token->type == TT_SEMICOLON)
		{
			*list = (*list)->next;
			node = ast_node_new(NT_EOF, node, pipeline(list,info),info);
		}
		else
			break;
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