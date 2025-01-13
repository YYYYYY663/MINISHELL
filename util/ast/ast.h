#ifndef AST_H
#define AST_H

#include "libft.h"
#include "sys.h"

typedef enum e_ntype
{
	NT_CMD,
	NT_PIPE,
	NT_EOF,
	NT_AND,
	NT_OR
}					t_ntype;


/* -------------------------------------------------------------------------- */
/*                                   STRUCT                                   */
/* -------------------------------------------------------------------------- */


typedef struct s_args
{
	char			path[PATH_MAX];
	char			**cargv;
	t_list			*argv;
	t_list			*redr;
	int				fds[2];
	pid_t			pid;
}					t_args;

struct s_ast
{
	struct s_ast	*left;
	struct s_ast	*right;
	t_ntype			ntype;
	t_args			*args;
};	


/* -------------------------------------------------------------------------- */
/*                                   FUNCS                                    */
/* -------------------------------------------------------------------------- */

void				ast_clear(t_ast *node);
char				**convert_argv(t_list *lst);
t_args				*ast_args_new(void);
t_ast				*ast_node_new(int type, t_ast *left, t_ast *right);
t_args				*consume_args(t_list **lst);

#endif