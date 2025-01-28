#include "ft_parser.h"

/**
 * @brief パーサーを起動し、トークンリストからASTを構築する
 *
 * この関数は以下の処理を行います：
 * 1. トークンリストの先頭を保持
 * 2. 式全体をパースしてASTを生成
 * 3. 生成したASTをinfo構造体に保存
 *
 * @param info シェル情報構造体（トークンリストとAST保存用）
 * @return t_status パース処理の結果（成功時はE_NONE）
 */
t_status	launch_parser(t_info *info)
{
	t_list	*head;

	head = info->token;
	if (((t_token *)head->data)->type == TT_EOF)
		return (E_NONE);
	info->ast = expr(&head, info);
	return (E_NONE);
}
