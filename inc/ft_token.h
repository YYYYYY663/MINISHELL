/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymizukam <ymizukam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 18:20:59 by teando            #+#    #+#             */
/*   Updated: 2025/01/29 19:47:36 by ymizukam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_TOKEN_H
# define FT_TOKEN_H

// typedef int			t_token_type;

// # define WORD_ID 0xF000 // WORD TYPE
//
/* -------------------------------------------------------------------------- */
// # define CMD_ARG 0x1000
// # define CONNECT 0x2000
// # define PIPE 0x3000
// # define PRIORITY 0x4000

// # define ARG_ID 0xF00 // COMMAND ARG TYPE
//
/* -------------------------------------------------------------------------- */
// # define WORD 0x100
// # define REDIRECT 0x200

// # define QUOTE_ID 0xF0 // coffee "coffee" 'coffee' only if WORDTYPE = CMD_ARG
//
/* -------------------------------------------------------------------------- */
// # define NO_QUOTE 0x00
// # define SINGLE_QUOTE 0x10
// # define DOUBLE_QUOTE 0x20

// // # define TT_WORD 0x1101

// # define REDIRECT_ID 0xFF0F // + QUOTE TYPE
//
/* -------------------------------------------------------------------------- */
// # define TT_REDIR_IN 0x1201
// # define TT_APPEND 0x1202
// # define TT_REDIR_OUT 0x1203
// # define TT_HEREDOC 0x1204

// # define CONNECT_ID 0xFFFF
//
/* -------------------------------------------------------------------------- */
// # define TT_AND_AND 0x2001
// # define TT_OR_OR 0x2002
// # define TT_SEMICOLON 0x2003
// # define TT_EOF 0x2004
// # define TT_ERROR 0xFFFF

// # define PRIORITY_ID 0xFFFF
//
/* -------------------------------------------------------------------------- */
// # define TT_LPAREN 0x4001
// # define TT_RPAREN 0x4002

# include "libft.h"
# include <limits.h>

# ifndef PATH_MAX
#  define PATH_MAX 2048
# endif

# define CMD_ARG 0x1000
# define CONNECT 0x2000
# define WORD 0x100
# define REDIRECT 0x200
# define SINGLE_QUOTE 0x010
# define DOUBLE_QUOTE 0x020

typedef int			t_token_type;

# define TT_WORD 0x1101
# define TT_PIPE 0x302
# define TT_REDIR_IN 0x1201
# define TT_APPEND 0x1202
# define TT_REDIR_OUT 0x1203
# define TT_HEREDOC 0x1204
# define TT_LPAREN 0x501
# define TT_RPAREN 0x502
# define TT_AND_AND 0x2001
# define TT_OR_OR 0x2002
# define TT_SEMICOLON 0x2003
# define TT_EOF 0x2004
# define TT_ERROR 0x002

# define TT_NOTWORD 0x00

typedef enum e_ntype
{
	NT_CMD,
	NT_PIPE,
	NT_EOF,
	NT_AND,
	NT_OR
}					t_ntype;

typedef struct s_cmd
{
	char			path[PATH_MAX];
	char			**cargv;
	t_list			*argv;
	t_list			*redr;
	int				fds[2];
	pid_t			pid;
	struct s_cmd	*next;
}					t_cmd;

typedef struct s_ast
{
	struct s_ast	*left;
	struct s_ast	*right;
	t_ntype			ntype;
	t_cmd			*args;
}					t_ast;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
}					t_token;

char				**convert_argv(t_list *lst);

t_cmd				*ast_cmd_new(void);
t_ast				*ast_node_new(int type, t_ast *left, t_ast *right);
int					consume(t_token_type type, t_list **lst);
void				expect(t_token_type type, t_list **lst);

t_cmd				*consume_args(t_list **lst);

t_token				*token_new(t_token_type type, char *value);

#endif