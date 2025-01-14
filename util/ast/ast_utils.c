/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymizukam <ymizukam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 22:16:26 by ymizukam          #+#    #+#             */
/*   Updated: 2025/01/14 12:35:44 by ymizukam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "sys.h"
#include "token.h"
#include "xunistd.h"

/**
 * @brief 引数を消費し、新しい引数リストを作成する
 *
 * この関数は以下の処理を行います：
 * 1. 新しい引数リスト構造体を作成
 * 2. CMD_ARG型のトークンのみを抽出
 * 3. トークンをコピーして新しいリストに追加
 *
 * @param lst 現在の引数リストの先頭を指すポインタ
 * @return t_args* 新しい引数リストの先頭を指すポインタ
 */
t_args	*consume_args(t_list **lst)
{
	t_args	*args;
	t_list	*new_lst;
	t_token	*token;
	t_token	*cpy;

	args = ast_args_new();
	if (!args)
		return (NULL);
	token = (t_token *)(*lst)->data;
	while ((token->type & WORD_ID) == CMD_ARG)
	{
		cpy = malloc(sizeof(t_token));
		cpy->type = token->type;
		cpy->value = ft_strdup(token->value);
		new_lst = ft_lstnew(cpy);
		if ((token->type & ARG_ID) == WORD)
			ft_lstadd_back(&args->argv, new_lst);
		if ((token->type & ARG_ID) == REDIRECT)
			ft_lstadd_back(&args->redr, new_lst);
		(*lst) = (*lst)->next;
		token = (t_token *)(*lst)->data;
	}
	return (args);
}

/**
 * @brief 次のトークンが期待する種類の場合、トークンを消費する
 *
 * この関数は以下の処理を行います：
 * 1. 現在のトークンの種類をチェック
 * 2. 期待する種類と一致する場合、トークンリストを進める
 *
 * @param type 期待するトークンの種類
 * @param lst トークンリストのポインタ
 * @return int 消費に成功した場合は1、失敗した場合は0
 */
int	consume(t_token_type type, t_list **lst)
{
	t_token	*token;

	token = (t_token *)(*lst)->data;
	if (type != token->type)
		return (0);
	*lst = (*lst)->next;
	return (1);
}

/**
 * @brief 次のトークンが期待する種類であることを確認し、トークンを進める
 *
 * この関数は以下の処理を行います：
 * 1. 現在のトークンの種類をチェック
 * 2. 期待する種類と一致しない場合は何もせずに返る
 * 3. 一致する場合はトークンリストを進める
 *
 * @param type 期待するトークンの種類
 * @param lst トークンリストのポインタ
 */
void	expect(t_token_type type, t_list **lst)
{
	t_token	*token;

	token = (t_token *)(*lst)->data;
	if (type != token->type)
	{
		return ;
	}
	*lst = (*lst)->next;
}

/**
 * @brief トークンの連結リストを文字列配列（argv形式）に変換する
 *
 * この関数は以下の処理を行います：
 * 1. トークン値からNULL終端の文字列配列を作成
 * 2. 配列と各文字列用のメモリを確保
 * 3. エラー発生時は確保したメモリを適切に解放
 *
 * @param lst t_token構造体の連結リスト
 * @return char** 文字列配列（argv形式）、エラー時はNULL
 */
char	**convert_argv(t_list *lst)
{
	char	**cargv;
	t_token	*token;
	size_t	i;

	if (!lst || !lst->data)
		return (NULL);
	cargv = ft_calloc(ft_lstsize(lst) + 1, sizeof(char *));
	if (!cargv)
		return (NULL);
	i = 0;
	while (lst)
	{
		token = lst->data;
		if (!token || !token->value)
			return (ft_strs_clear(cargv), NULL);
		cargv[i] = ft_strdup(token->value);
		if (!cargv[i])
			return (ft_strs_clear(cargv), NULL);
		i++;
		lst = lst->next;
	}
	cargv[i] = NULL;
	return (cargv);
}
