/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 18:20:59 by teando            #+#    #+#             */
/*   Updated: 2024/12/23 02:27:48 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

# include "libft.h"

typedef enum e_token_type
{
	TT_CMD,          // コマンドトークン
	TT_PIPE,         // パイプ
	TT_REDIRECT_IN,  // 入力リダイレクト
	TT_REDIRECT_OUT, // 出力リダイレクト
	TT_APPEND,       // 追記リダイレクト
	TT_HEREDOC,      // ヒアドキュメント
	TT_LPAREN,       // (
	TT_RPAREN,       // )
	TT_AND_AND,      // &&
	TT_OR_OR,        // ||
	TT_SEMICOLON,    // ;
	TT_EOF,          // 終端
	TT_ERROR         // エラー
}						t_token_type;

//外に出さないとこれをnewする関数が作れない。。。
// todo それぞれnew, free, aplly関数を作る
typedef struct s_ast_node
{
	enum
	{
		NT_CMD,      // words and redirects head ptr
		NT_PIPE,     // |
		NT_PRIORITY, // ()
		NT_EOP,      // && || ; EOF
	} e_type;
	union
	{
		t_list *args; // CMDのitems WORDとリダイレクトの先頭ポインタ
		int				pipefds[2];
		int				priority_level;
		t_token_type	eop_type;
	} u_val;
}						t_ast_node_item;

typedef struct s_token
{
	t_token_type		type;
	char				**value;
}						t_token;

#endif