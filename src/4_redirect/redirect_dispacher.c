#include "ft_redirect.h"


t_status redirect_dipacher(t_list *list, int *in_fd, int *out_fd, t_info *info)
{
    t_token *token;
    while(list != NULL)
    {
        token = list->data;
        if (token->type == TT_HEREDOC)
        {
            xclose(in_fd);
            in_fd = heredoc(token->value, info);
        }



        list = list->next;
    }


    return E_NONE;
}