/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymizukam <ymizukam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 22:16:26 by ymizukam          #+#    #+#             */
/*   Updated: 2025/01/04 22:47:36 by ymizukam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_system.h"
#include "ft_token.h"
#include "xunistd.h"

void	ast_clear(t_ast *node)
{
#ifdef CLEAR_OUT
	printf("%s\n", __func__);
#endif
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
	}
	free(node);
}
