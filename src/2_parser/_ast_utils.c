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
        new_lst = ft_lstnew(token);
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