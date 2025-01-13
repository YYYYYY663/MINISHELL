#include "ft_lexer.h"
const char	*type_to_str(t_token_type t)
{
	if ((t & ARG_ID) == WORD)
		return ("TT_WORD");
	if ((t & WORD_ID) == PIPE)
		return ("TT_PIPE");
	if (t == TT_REDIR_IN)
		return ("TT_REDIR_IN");
	if (t == TT_APPEND)
		return ("TT_APPEND");
	if (t == TT_REDIR_OUT)
		return ("TT_REDIR_OUT");
	if (t == TT_HEREDOC)
		return ("TT_HEREDOC");
	if (t == TT_LPAREN)
		return ("TT_LPAREN");
	if (t == TT_RPAREN)
		return ("TT_RPAREN");
	if (t == TT_AND_AND)
		return ("TT_AND_AND");
	if (t == TT_OR_OR)
		return ("TT_OR_OR");
	if (t == TT_SEMICOLON)
		return ("TT_SEMICOLON");
	if (t == TT_EOF)
		return ("TT_EOF");
	return ("TT_ERROR");
}

void	debug_print_token_list(t_list *list)
{
	t_token	*tok;

	while (list)
	{
		tok = (t_token *)list->data;
		ft_printf("type: %s, value: ", type_to_str(tok->type));
		if (tok->value)
			ft_printf("[%s]\n", tok->value);
		else
			ft_printf("NULL\n");
		list = list->next;
	}
}
