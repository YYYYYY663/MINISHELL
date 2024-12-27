#include "ft_redirect.h"
#include "ft_env.h"
#include "ft_lexer.h"
#include "xunistd.h"


t_status redirect_dipacher(t_list *list, int *in_fd, int *out_fd, t_info *info)
{
    t_token *token;
    // char path[PATH_MAX];
    while(list != NULL)
    {
        token = list->data;
        #ifdef FUNC_OUT
        printf("%s %s\n", type_to_str(token->type), token->value);
        #endif


        if (token->type == TT_HEREDOC)
        {
            xclose(in_fd);
            *in_fd = heredoc(token->value, info);
        }
        if (token->type == TT_REDIR_IN)
        {
            xclose(in_fd);
            // if (path_dispacher(path,token->value,R_OK,info))
            // {
            //     perror(token->value);
            //     xclose(out_fd);
            //     return (E_FILE); 
            // }
            *in_fd = open(token->value,O_RDONLY);
            if (*in_fd == -1)
            {
                perror(token->value);
                xclose(out_fd);
                return (E_FILE); 
            }
        }
        if (token->type == TT_REDIR_OUT)
        {
            xclose(out_fd);
            *out_fd = open(token->value, O_WRONLY | O_CREAT | O_TRUNC, 0666);
            if (*out_fd == -1)
            {
                perror(token->value);
                xclose(in_fd);
                return (E_FILE); 
            }
        }
        if (token->type == TT_APPEND)
        {
            xclose(out_fd);
            *out_fd = open(token->value, O_WRONLY | O_CREAT | O_APPEND, 0666);
            if (*out_fd == -1)
            {
                perror(token->value);
                xclose(in_fd);
                return (E_FILE); 
            }
        }


        list = list->next;
    }


    return E_NONE;
}