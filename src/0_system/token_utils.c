#include "ft_system.h"
#include "ft_token.h"

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


void token_clear(void *ptr)
{
	#ifdef CLEAR_OUT
		printf("%s\n",__func__);
	#endif
	t_token *token = (t_token *)ptr; 
	if (token == NULL)
        return ;
	if (token->value)
    	free(token->value);
    free(token);
}
