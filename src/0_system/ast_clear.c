/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_clear.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymizukam <ymizukam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 20:06:36 by ymizukam          #+#    #+#             */
/*   Updated: 2024/12/24 20:13:34 by ymizukam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_system.h"
#include "ft_token.h"

void	ast_clear(t_ast *node)
{
	if (!node)
		return ;
	ast_clear(node->left);
	ast_clear(node->right);
	if (node->args)
	{
		ft_list_clear(&node->args);
	}
	free(node);
}
