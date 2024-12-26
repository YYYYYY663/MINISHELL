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


t_args *ast_args_new(t_info *info)
{
    (void)info;
    t_args *args = ft_calloc(1, sizeof(t_args));
    args->fds[0] = -1;
    args->fds[1] = -1;
    args->pid = -1;

    return args;
}

t_ast	*ast_node_new(int type, t_info *info)
{

	t_ast	*node;
    (void)info;
	//new_node = xmalloc(sizeof(t_ast), info);
    node = ft_calloc(1,sizeof(t_ast));
	node->ntype = type;
	return (node);
}

t_args	*consume_args(t_list **lst, t_info *info)
{
	t_args	*args = ast_args_new(info);
	t_token *token = (t_token *)(*lst)->data;
	while ((token->type & 0xF000) == CMD_ARG)
	{
        if (token->type == TT_WORD)
		    ft_lstadd_back(&args->cmd, *lst);//todo *lstのコピーを渡さなければならない！！！！！
        if (token->type == TT_HEREDOC || token->type == TT_REDIR_IN)
            ft_lstadd_back(&args->rd_i, *lst);
        if (token->type == TT_APPEND || token->type == TT_REDIR_OUT)
            ft_lstadd_back(&args->rd_o, *lst);
        (*lst) = (*lst)->next;
        token = (t_token *)(*lst)->data;
	}
    return args;
}

// WORDが来たら 
// todo (がさきに来た時の対策も
//最初に|, && ||がきたらsyntax error
t_ast	*ast_pipeline_new(t_list *list, t_info *info)
{
    #ifdef FUNC_OUT
		printf("%s\n",__func__);
	#endif
	t_ast	*pipe_node;
	t_ast	*current_node;
	t_token *token = (t_token *)list->data;

	pipe_node = ast_node_new(NT_PIPE, info);
	current_node = pipe_node;
	while (1)//まず読むのはWORD REDIRのどれか
	{
		current_node->left = ast_node_new(NT_CMD ,info);
        //leftにargsを加えていく
        current_node->left->args = consume_args(&list,info);


        token = (t_token *)list->data;
        if (token->type != TT_PIPE)
            break;
		current_node->right = ast_node_new(NT_PIPE, info);
        list = list->next;
		current_node = current_node->right;
	}
    //pipe以外のものがきたら抜ける（bonus)
	return (pipe_node);
}



// t_ast	*ast_root_new(char **argv, t_info *info)
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