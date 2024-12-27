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

pid_t	cmd_node(t_ast *node, int in_fd, int out_fd, t_info *info)
{
	#ifdef FUNC_OUT
		printf("%s node: %s\n",__func__, e_type_to_str(node->ntype));
	#endif
	pid_t	pid;
	char	path[PATH_MAX];

	//ここの処理怪しい
	if (node->ntype == NT_PIPE)
		return(cmd_node(node->left, in_fd, out_fd, info));

	//cmd, rd_i, rd_oの変数展開
	//redirectの解決
	char 	**argv = ft_list_to_strs(node->args->argv);
	#ifdef FUNC_OUT
		ft_putstrs_endl_fd(argv,"\n",2);
	#endif

	// if (in_fd == -1 || out_fd == -1)
	// 	return (-1);
	
	pid = xfork(info);
	if (pid == 0)
	{
		#ifdef FUNC_OUT
			dprintf(2,"in: %d\tout: %d\n",in_fd,out_fd);
		#endif
		if (in_fd != STDIN_FILENO)
		{
			dup2(in_fd, STDIN_FILENO);
			xclose(&in_fd);
		}
		if (out_fd!=STDOUT_FILENO)
		{
			dup2(out_fd, STDOUT_FILENO);
			xclose(&out_fd);
		}
		#ifdef FUNC_OUT
			dprintf(2,"in: %d\tout: %d\n",in_fd,out_fd);
		#endif
		// if (fetch_absolutepath(path, *node->args, info->env_path, X_OK))
		// 	process_exit(*node->args);
		// execve(path, node->args, );
		execvp(argv[0], argv);
		exit(1);
		// process_exit(*node->args);
	}
	return (pid);
}

t_status pipe_node(t_ast *node, int in_fd, int out_fd, t_info *info)
{
	#ifdef FUNC_OUT
		printf("%s\n",__func__);
	#endif
	int pipefds[2];
	int status = 0;
	if (node->right != NULL)
	{
		xpipe(pipefds, info);
		// if (node->left->ntype != NT_CMD)
		// 	traverse_ast_nodes(node,info);
		cmd_node(node->left, in_fd, pipefds[1], info);
		xclose(&pipefds[1]);
		pipe_node(node->right, pipefds[0], out_fd, info);
		xclose(&pipefds[0]);
	}
	else
	{
		//todo builtinの確認
		// if (node->left->ntype != NT_CMD)
		// 	traverse_ast_nodes(node,info);
		waitpid(cmd_node(node->left, in_fd, out_fd, info), &status, 0);
		// xclose(&in_fd);
	}
	return ((t_status)status);
}


t_status exec_pipeline(t_ast *node, t_info *info)
{
	#ifdef FUNC_OUT
		printf("%s\n",__func__);
	#endif
	//ここの処理怪しい
	if (node->left->ntype == NT_CMD)
		return pipe_node(node, STDIN_FILENO, STDOUT_FILENO, info);
	else
		return (traverse_ast_nodes(node->left, info));
}


t_status	traverse_ast_nodes(t_ast *node, t_info *info)
{
	t_status status;
	if (node == NULL)
		return (E_NONE);
	if (g_signal)
		return ((t_status)g_signal);
	#ifdef FUNC_OUT
		printf("%s node: %s\n",__func__, e_type_to_str(node->ntype));
	#endif
	
	// if (node->ntype == NT_CMD)pipeの中で処理する

	if (node->ntype == NT_PIPE)
		return exec_pipeline(node, info);
	
	if (node->ntype == NT_AND)
	{
		status = traverse_ast_nodes(node->left, info);
		if (!status)
			return(traverse_ast_nodes(node->right, info));

	}
	if (node->ntype == NT_OR)
	{
		status = traverse_ast_nodes(node->left, info);
		if (status)
			return(traverse_ast_nodes(node->right, info));
	}

	if (node->ntype == NT_EOF)
	{
		status = traverse_ast_nodes(node->left, info);
		status = traverse_ast_nodes(node->right, info);
	}

	return status;
}