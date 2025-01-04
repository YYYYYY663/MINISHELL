/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymizukam <ymizukam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 22:16:26 by ymizukam          #+#    #+#             */
/*   Updated: 2025/01/05 04:36:51 by ymizukam         ###   ########.fr       */
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
		printf("args clear\n");
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
		// if (!cpy)
		// 	return (free(args), NULL);
		cpy->type = token->type;
		cpy->value = ft_strdup(token->value);
		new_lst = ft_lstnew(cpy);
		// if (!new_lst)
		// {
		// 	return (free(args), NULL);
		// }
		if (token->type == TT_WORD)
			ft_lstadd_back(&args->argv, new_lst);
		if (token->type == TT_HEREDOC || token->type == TT_REDIR_IN)
			ft_lstadd_back(&args->redr, new_lst);
		if (token->type == TT_APPEND || token->type == TT_REDIR_OUT)
			ft_lstadd_back(&args->redr, new_lst);
		//(*lst)->data = NULL;
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
		// printf("expected %d", type);
		// system_exit()
	}
	*lst = (*lst)->next;
}
