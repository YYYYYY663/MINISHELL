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

t_status launch_parser(t_info *info);

t_btree	*parse_tokens(t_info *info);

/*
** デバッグ用: AST の中身 (t_ast_node_item) を再帰的に表示
** depth はインデント用
*/
void	debug_print_ast(t_btree *root, int depth);


#endif