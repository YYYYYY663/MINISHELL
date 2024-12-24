/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 18:20:59 by teando            #+#    #+#             */
/*   Updated: 2024/12/24 19:42:32 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

# include "libft.h"

typedef enum e_token_type
{
	TT_WORD,      // text
	TT_PIPE,      // |
	TT_REDIR_IN,  // <
	TT_APPEND,    // >>
	TT_REDIR_OUT, // >
	TT_HEREDOC,   // <<
	TT_LPAREN,    // (
	TT_RPAREN,    // )
	TT_AND_AND,   // &&
	TT_OR_OR,     // ||
	TT_SEMICOLON, // ;
	TT_EOF,       // 終端
	TT_ERROR      // エラー
}					t_token_type;

// todo それぞれnew, free, aplly関数を作る
// typedef struct s_ast_node_item
// 外に出さないとこれをnewする関数が作れない。。。
//  todo それぞれnew, free, aplly関数を作る
typedef struct s_ast
{
	struct s_ast	*left;
	struct s_ast	*right;
	enum
	{
		NT_CMD,      // words and redirects
		NT_PIPE,     // |
		NT_PRIORITY, // ()
		NT_EOF,      // ; EOF
		NT_AND,
		NT_OR
	} e_type;
	t_list *args; // CMDの時のみ使用 WORDとREDIRの線形リスト
}					t_ast;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
}					t_token;

#endif