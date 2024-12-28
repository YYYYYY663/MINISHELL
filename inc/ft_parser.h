/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 19:27:53 by teando            #+#    #+#             */
/*   Updated: 2024/12/17 19:30:53 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PARSER_H
# define FT_PARSER_H

# include "ft_lexer.h"
# include "ft_system.h"
# include "ft_token.h"

/*
** parse_tokens:
**   info->token_list を読んで、AST (t_btree*) を構築。
**   戻り値: ASTのルートノード (t_btree*)。エラー時はNULL。
*/


const char	*e_type_to_str(int t);

t_status launch_parser(t_info *info);

// t_btree	*parse_tokens(t_info *info);

t_ast	*pipeline(t_list **list, t_info *info);
t_ast	*expr(t_list **list, t_info *info);

t_args	*consume_args(t_list **lst, t_info *info);
t_args *ast_args_new(t_info *info);
t_ast	*ast_node_new(int type, t_ast *left, t_ast *right, t_info *info);
int 	consume(t_token_type type, t_list **lst);
void     expect(t_token_type type, t_list **lst);
/*
** デバッグ用: AST の中身 (t_ast_node_item) を再帰的に表示
** depth はインデント用
*/

void	debug_print_ast(t_ast *ast, int depth);


#endif