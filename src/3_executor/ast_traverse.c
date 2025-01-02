/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_traverse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymizukam <ymizukam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 16:28:15 by ymizukam          #+#    #+#             */
/*   Updated: 2024/12/22 16:55:08 by ymizukam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_executor.h"
#include "ft_system.h"
#include "ft_token.h"
#include "ft_parser.h"
/*
 * CMDの処理はpreでもinでもどこでも大丈夫
 * signal handlingのためにすべてにifcheckをいれるべき
 */
int g_signal = 0;


t_status exec_pipeline(t_ast *node, t_info *info)
{
	#ifdef FUNC_OUT
		printf("%s\n",__func__);
	#endif
	if (node->left->ntype == NT_CMD)
		return pipe_node(node, STDIN_FILENO, STDOUT_FILENO, info);
	else
		return (traverse_ast_nodes(node->left, info));
}


void    kill_pipeline(t_ast *node, t_info *info)
{
	#ifdef FUNC_OUT
        printf("%s\n",__func__);
    #endif

	(void)info;
	if (node == NULL)
		return ;
    if (node->ntype == NT_CMD)
	{

		waitpid(node->args->pid,NULL,SIGTERM); 
		//kill(node->args->pid,SIGTERM);
		//perror(node->args->cargv[0]);
	}
	kill_pipeline(node->right,info);
	kill_pipeline(node->left,info);
}


t_status	traverse_ast_nodes(t_ast *node, t_info *info)
{
	if (node == NULL)
		return (E_NONE);
	if (g_signal)
		return ((t_status)g_signal);
	if (node->ntype == NT_PIPE)
	{
		exec_pipeline(node, info);
		kill_pipeline(node->left, info);
		printf("status %d\n", info->status);
		free(info->env_spc['?']);
		info->env_spc['?'] = ft_itoa(info->status);
		return E_NONE;
	}
	
	if (node->ntype == NT_AND)
	{
		traverse_ast_nodes(node->left, info);
		if (!info->status)
			return traverse_ast_nodes(node->right, info);
	}
	else if (node->ntype == NT_OR)
	{
		traverse_ast_nodes(node->left, info);

		if (info->status)
			return traverse_ast_nodes(node->right, info);
	}
	else if (node->ntype == NT_EOF)
	{
		traverse_ast_nodes(node->left, info);
		traverse_ast_nodes(node->right, info);
	}
	return E_NONE;
}