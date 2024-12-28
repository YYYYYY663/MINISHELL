/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymizukam <ymizukam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 18:20:59 by teando            #+#    #+#             */
/*   Updated: 2024/12/24 20:13:07 by ymizukam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

#include "libft.h"
#include <limits.h>

# ifndef PATH_MAX
#  define PATH_MAX 2048
# endif

#define CMD_ARG       0x1000 // Command arguments
#define CONNECT       0x2000 // &&, ||, ;
#define WORD          0x100 // General words
#define REDIRECT      0x200 // Redirection
#define SINGLE_QUOTE  0x010 // Single quote
#define DOUBLE_QUOTE  0x020 // Double quote

/*
* USAGE
* 0x300 | SINGLE_QUOTE 'HI WHATS UP!'
* []
*/

typedef enum e_token_type
{
    TT_WORD = 0x1101,        // Text
    TT_PIPE = 0x302,        // |
    TT_REDIR_IN = 0x1201,    // <
    TT_APPEND = 0x1202,      // >>
    TT_REDIR_OUT = 0x1203,   // >
    TT_HEREDOC = 0x1204,     // <<
    TT_LPAREN = 0x501,      // (
    TT_RPAREN = 0x502,      // )
    TT_AND_AND = 0x2001,     // &&
    TT_OR_OR = 0x2002,       // ||
    TT_SEMICOLON = 0x2003,   // ;
    TT_EOF = 0x2004,         // End of file
    TT_ERROR = 0x002        // Error
} t_token_type;


typedef enum e_ntype
{
	NT_CMD,      // words and redirects
	NT_PIPE,     // |
	NT_EOF,      // ; EOF
	NT_AND,
	NT_OR
} t_ntype;


typedef struct s_args
{
	char path[PATH_MAX];
	char **cargv;
	t_list *argv;
	t_list *redr;
	int fds[2];
	pid_t pid;
} t_args;


typedef struct s_ast
{
	struct s_ast	*left;
	struct s_ast	*right;
	t_ntype ntype;
	t_args *args; // CMDの時のみ使用 WORDとREDIRの線形リスト
}					t_ast;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
}					t_token;


char **convert_argv(t_list *lst);


#endif