/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymizukam <ymizukam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 18:20:59 by teando            #+#    #+#             */
/*   Updated: 2025/01/05 02:43:35 by ymizukam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

# include "libft.h"
# include <limits.h>

# ifndef PATH_MAX
#  define PATH_MAX 2048
# endif

# define CMD_ARG 0x1000     // Command arguments
# define CONNECT 0x2000     // &&, ||, ;
# define WORD 0x100         // General words
# define REDIRECT 0x200     // Redirection
# define SINGLE_QUOTE 0x010 // Single quote
# define DOUBLE_QUOTE 0x020 // Double quote

typedef int			t_token_type;

# define TT_WORD 0x1101 // Text
# define TT_PIPE 0x302 // |
# define TT_REDIR_IN 0x1201 // <
# define TT_APPEND 0x1202 // >>
# define TT_REDIR_OUT 0x1203 // >
# define TT_HEREDOC 0x1204 // <<
# define TT_LPAREN 0x501 // (
# define TT_RPAREN 0x502 // )
# define TT_AND_AND 0x2001 // &&
# define TT_OR_OR 0x2002 // ||
# define TT_SEMICOLON 0x2003 // ;
# define TT_EOF 0x2004 // End of file
# define TT_ERROR 0x002 // Error

typedef enum e_ntype
{
	NT_CMD,  // words and redirects
	NT_PIPE, // |
	NT_EOF,  // ; EOF
	NT_AND,
	NT_OR
}					t_ntype;

typedef struct s_args
{
	char			path[PATH_MAX];
	char			**cargv;
	t_list			*argv;
	t_list			*redr;
	int				fds[2];
	pid_t			pid;
}					t_args;

typedef struct s_ast
{
	struct s_ast	*left;
	struct s_ast	*right;
	t_ntype			ntype;
	t_args			*args;
}					t_ast;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
}					t_token;

char				**convert_argv(t_list *lst);

t_args				*ast_args_new(void);
t_ast				*ast_node_new(int type, t_ast *left, t_ast *right);
int					consume(t_token_type type, t_list **lst);
void				expect(t_token_type type, t_list **lst);

t_args				*consume_args(t_list **lst);

#endif