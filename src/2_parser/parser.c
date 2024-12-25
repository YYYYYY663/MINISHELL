#include "ft_parser.h"
t_status launch_parser(t_info *info)
{
    t_ast *ast = aligne_token(info);
    return E_NONE;
}


t_ast	*ast_node_new(int type, t_list *args, t_info *info)
{
	t_ast	*new_node;

	new_node = xmalloc(sizeof(t_ast), info);
	new_node->e_type = type;
	new_node->args = args;
	return (new_node);
}


t_list *consume(int type, t_list **lst)
{
    t_list *ret = *lst;
    t_token *token;
    while(1)
    {
        token = (t_token *)(*lst)->data;
        if (token->type & CMD_ARG == 0)
            break;
        //コピーしたっ方が良さそう?
        ft_lstadd_back(&ret, *lst);
        *lst = (*lst)->next;
    }
    return (ret);
}

t_list *expect(int type, t_list **lst)
{
    t_token *token = (t_token *)(*lst)->data;
    if (token->type != type)
        return *lst;
    *lst = (*lst)->next;
    return (NULL);

}

t_status  aligne_token(t_info *info)
{
    t_list *lst = info->token_list;
    t_token *token;
    t_ast *ast = info->ast;
    t_ast *cur = ast;
    while(1)
    {
        token = (t_token *)lst->data;
        //CMDの引数になりそうな場合consumeでCMD_ARGで無くなるまで進める
        if (token->type & CMD_ARG)
            ast->right = ast_node_new(token->type, consume(CMD_ARG, &lst), info);
        else
            ast->right = ast_node_new(token->type, expect(token->type, &lst), info);
        
        if (token->type == TT_EOF)
            break;
        cur = cur->right;
    }
}
