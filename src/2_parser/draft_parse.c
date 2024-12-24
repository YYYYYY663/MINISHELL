#include "ft_parser.h"
static t_list			*g_cur_token = NULL; // 現在参照中のトークンノード
static t_info			*g_info = NULL;

/* 今のトークンを返す */
static t_token	*current_token(void)
{
	if (!g_cur_token)
		return (NULL);
	return ((t_token *)g_cur_token->data);
}

/* 次のトークンへ進む */
static void	advance(void)
{
	if (g_cur_token)
		g_cur_token = g_cur_token->next;
}

/* consume: 引数typeと一致したら進めて1、一致しなければ0 */
static int	consume(t_token_type type)
{
	t_token	*tok;

	tok = current_token();
	if (tok && tok->type == type)
	{
		advance();
		return (1);
	}
	return (0);
}

/*
** t_btreeノードを新規作成し、item に t_ast* を格納
** left,right は NULL 初期化
*/
static t_btree	*new_btree_node(t_ast *content)
{
	t_btree	*node;

	node = ft_calloc(1, sizeof(t_btree));
	if (!node)
	{
		g_info->status = E_ALLOCATE;
		return (NULL);
	}
	node->item = content;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

/*
** t_ast を生成
**  e_type: NT_CMD, NT_PIPE, NT_EOP, etc.
*/
static t_ast	*new_ast_item(int e_type)
{
	t_ast	*ast;

	ast = ft_calloc(1, sizeof(t_ast));
	if (!ast)
	{
		g_info->status = E_ALLOCATE;
		return (NULL);
	}
	ast->e_type = e_type;
	return (ast);
}

/*
** parse_single_command:
**   - 連続する TT_WORD を1つのNT_CMDノードにまとめる
**   - WORDが無ければ NULL
*/
static t_btree	*parse_single_command(void)
{
	t_ast	*ast_cmd;
	t_list			*args_head;
	t_list			*args_tail;
	t_token			*tok;
	t_list			*new_node;
	t_btree			*tree_node;

	// 次のトークンが WORD でなければコマンドなし
	if (!current_token() || current_token()->type != TT_WORD)
		return (NULL);
	// ASTノード: NT_CMD
	ast_cmd = new_ast_item(NT_CMD);
	if (!ast_cmd)
		return (NULL);
	// 空のリストを格納していく
	args_head = NULL;
	args_tail = NULL;
	// 連続する TT_WORD を収集
	while (current_token() && current_token()->type == TT_WORD)
	{
		tok = current_token();
		// ここでは新しいリストノードを生成して tok->value を格納
		new_node = ft_calloc(1, sizeof(t_list));
		if (!new_node)
		{
			g_info->status = E_ALLOCATE;
			return (NULL);
		}
		new_node->data = tok->value; // "a" や "b" 等
		new_node->next = NULL;
		// リスト末尾に追加
		if (!args_head)
		{
			args_head = new_node;
			args_tail = new_node;
		}
		else
		{
			args_tail->next = new_node;
			args_tail = new_node;
		}
		advance(); // トークン消費
	}
	// 収集した引数リストを ASTノードにセット
	ast_cmd->args = args_head;
	// btreeノード化
	tree_node = new_btree_node(ast_cmd);
	return (tree_node);
}

/*
** parse_tokens
**   - とりあえず 1行につきNT_CMDを1つだけ構築し、残りのWORDも全部そのargsに入れる。
**   - 実際のミニシェルでは、パイプ/リダイレクト/&&などに合わせて複数ノードを作るが、
**     今回はサンプルで "a b c" を単一のNT_CMD(args=[a,b,c])にしたいので簡易実装。
*/
t_btree	*parse_tokens(t_info *info)
{
	t_btree	*root;

	g_info = info;
	g_cur_token = info->token_list;
	info->status = E_NONE;
	// コマンドを1つパース
	root = parse_single_command();
	// あとは EOF を consume して終わり
	consume(TT_EOF);
	return (root); // rootはNT_CMDの1ノードのみ
}