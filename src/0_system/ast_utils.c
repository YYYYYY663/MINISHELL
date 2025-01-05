/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymizukam <ymizukam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 22:16:26 by ymizukam          #+#    #+#             */
/*   Updated: 2025/01/06 06:39:17 by ymizukam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_system.h"
#include "ft_token.h"
#include "xunistd.h"

void	ast_clear(t_ast *node)
{
	if (node == NULL)
		return ;
	ast_clear(node->left);
	ast_clear(node->right);
	if (node->args)
	{
		if (node->args->argv)
			ft_lstclear(&node->args->argv, token_clear);
		if (node->args->redr)
			ft_lstclear(&node->args->redr, token_clear);
		if (node->args->cargv)
			ft_strs_clear(node->args->cargv);
		xclose(&node->args->fds[0]);
		xclose(&node->args->fds[1]);
		if (node->args->pid != -1)
			waitpid(node->args->pid, NULL, 0);
		free(node->args);
	}
	free(node);
}

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
	while ((token->type & 0xF000) == CMD_ARG)
	{
		cpy = malloc(sizeof(t_token));
		cpy->type = token->type;
		cpy->value = ft_strdup(token->value);
		new_lst = ft_lstnew(cpy);
		if (token->type == TT_WORD)
			ft_lstadd_back(&args->argv, new_lst);
		if ((token->type & 0xF00) == REDIRECT)
			ft_lstadd_back(&args->redr, new_lst);
		(*lst) = (*lst)->next;
		token = (t_token *)(*lst)->data;
	}
	return (args);
}

t_args	*ast_args_new(void)
{
	t_args	*args;

	args = ft_calloc(1, sizeof(t_args));
	if (args == NULL)
		return (NULL);
	args->fds[0] = -1;
	args->fds[1] = -1;
	args->pid = -1;
	return (args);
}

t_ast	*ast_node_new(int type, t_ast *left, t_ast *right)
{
	t_ast	*node;

	node = ft_calloc(1, sizeof(t_ast));
	if (!node)
		return (NULL);
	node->ntype = type;
	node->left = left;
	node->right = right;
	return (node);
}

// 次のトークンが期待している記号のときには、トークンを1つ読み進めて
// 真を返す。それ以外の場合には偽を返す。
int	consume(t_token_type type, t_list **lst)
{
	t_token	*token;

	token = (t_token *)(*lst)->data;
	if (type != token->type)
		return (0);
	*lst = (*lst)->next;
	return (1);
}

// 次のトークンが期待している記号のときには、トークンを1つ読み進める。
// それ以外の場合にはエラーを報告する。
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
