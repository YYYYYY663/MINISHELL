/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draft_parser_debug.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymizukam <ymizukam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 21:52:24 by teando            #+#    #+#             */
/*   Updated: 2025/01/04 22:25:21 by ymizukam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_parser.h"
#include "ft_token.h"

/**
 * @brief ノードタイプを文字列に変換する
 * 
 * この関数は以下のノードタイプを文字列に変換します：
 * - NT_CMD  → "NT_CMD" （コマンドノード）
 * - NT_PIPE → "NT_PIPE"（パイプノード）
 * - NT_AND  → "NT_AND" （AND論理演算子ノード）
 * - NT_EOF  → "NT_EOF" （セミコロンノード）
 * - NT_OR   → "NT_OR"  （OR論理演算子ノード）
 * 
 * @param t ノードタイプ
 * @return const char* 対応する文字列、未知の型の場合は"UNKNOWN"
 */
const char	*e_type_to_str(int t)
{
	if (t == NT_CMD)
		return ("NT_CMD");
	if (t == NT_PIPE)
		return ("NT_PIPE");
	if (t == NT_AND)
		return ("NT_AND");
	if (t == NT_EOF)
		return ("NT_EOF");
	if (t == NT_OR)
		return ("NT_OR");
	return ("UNKNOWN");
}

/**
 * @brief ASTをデバッグ用に再帰的に表示する
 * 
 * この関数は以下の処理を行います：
 * 1. インデントを深さに応じて出力
 * 2. ノードの種類を表示
 * 3. コマンドノードの場合は引数リストを表示
 * 4. 左右の子ノードを再帰的に表示（深さを増やして）
 * 
 * 出力形式：
 * [ノードタイプ] args=[引数1, 引数2, ...]
 *   [子ノード1]
 *   [子ノード2]
 * 
 * @param ast 表示するASTノード
 * @param depth 現在の深さ（インデント用）
 */
void	debug_print_ast(t_ast *ast, int depth)
{
	t_list	*p;
	char	*word;
	t_token	*token;

	if (!ast)
		return ;
	for (int i = 0; i < depth; i++)
		ft_dprintf(STDOUT_FILENO, "  ");
	if (!ast)
	{
		ft_dprintf(STDOUT_FILENO, "(null)\n");
		return ;
	}
	ft_dprintf(STDOUT_FILENO, "[%s]", e_type_to_str(ast->ntype));
	if (ast->ntype == NT_CMD && ast->args)
	{
		ft_dprintf(STDOUT_FILENO, " args=[");
		p = ast->args->argv;
		while (p)
		{
			token = (t_token *)p->data;
			word = token->value;
			ft_dprintf(STDOUT_FILENO, "%s", word);
			p = p->next;
			if (p)
				ft_dprintf(STDOUT_FILENO, ", ");
		}
		ft_dprintf(STDOUT_FILENO, "]");
	}
	ft_dprintf(STDOUT_FILENO, "\n");
	debug_print_ast(ast->left, depth + 1);
	debug_print_ast(ast->right, depth + 1);
}
