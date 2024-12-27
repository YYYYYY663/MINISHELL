#include "ft_executor.h"
#include "ft_system.h"
#include "ft_token.h"
#include "ft_redirect.h"
#include "ft_parser.h"
#include "ft_env.h"



char **convert_argv(t_list *lst)
{
    char **cargv = ft_calloc(ft_lstsize(lst)+1, sizeof(char *));
    t_token *token = (t_token *)lst->data;
    char **ptr = cargv;
    while(lst != NULL)
    {
        *ptr++ = token->value;//ft_strdup(token->value);
        lst = lst->next;
        token = (t_token *)lst->data;

    }
    return cargv;
}


int setup_args(t_args *args, int *in_fd, int *out_fd, t_info *info)
{
    //まずはredrとargvの変数展開
    //redirectの用意
    if (redirect_dipacher(args->redr, in_fd, out_fd, info))
    {
        return 1;
    }
    //pathの取得
    t_token *token = (t_token *) args->argv->data;
    if (token->value == NULL)
    {
        return 1;//redirectしかない場合
    }
    if (path_dispacher(args->path,token->value, X_OK, info))
    {
        perror(token->value);
        return 1;
    }
    args->cargv = convert_argv(args->argv);

    return 0;
}