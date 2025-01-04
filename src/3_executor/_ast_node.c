/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _ast_node.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymizukam <ymizukam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 22:17:59 by ymizukam          #+#    #+#             */
/*   Updated: 2025/01/05 00:28:10 by ymizukam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_builtin.h"
#include "ft_executor.h"
#include "ft_parser.h"
#include "ft_system.h"
#include "ft_token.h"
#include <signal.h>
/*
 * CMDの処理はpreでもinでもどこでも大丈夫
 * signal handlingのためにすべてにifcheckをいれるべき
 */

pid_t	cmd_node(t_ast *node, int in_fd, int out_fd, t_info *info)
{
	pid_t	pid;

#ifdef FUNC_OUT
	printf("%s node: %s\n", __func__, e_type_to_str(node->ntype));
#endif
	//ここの処理怪しい
	if (node->ntype == NT_PIPE)
		return (cmd_node(node->left, in_fd, out_fd, info));
	if (setup_args(node->args, &in_fd, &out_fd, info))
		return (-1);
	pid = xfork(info);
	if (pid == 0)
	{
#ifdef FUNC_OUT
		dprintf(2, "in: %d\tout: %d\n", in_fd, out_fd);
#endif
		xdup2(in_fd, STDIN_FILENO, info);
		xdup2(out_fd, STDOUT_FILENO, info);
#ifdef FUNC_OUT
		dprintf(2, "in: %d\tout: %d\n", in_fd, out_fd);
#endif
		execve(node->args->path, node->args->cargv,
			ft_list_to_strs(info->env_map));
		perror("execve");
		exit(1);
	}
	xclose(&in_fd);
	xclose(&out_fd);
	// node->args->fds[0] = in_fd;
	// node->args->fds[1] = out_fd;
	node->args->pid = pid;
	return (pid);
}

t_status	pipe_node(t_ast *node, int in_fd, int out_fd, t_info *info)
{
	int		pipefds[2];
	int		status;
	pid_t	pid;

#ifdef FUNC_OUT
	printf("%s\n", __func__);
#endif
	status = 0;
	if (node->right != NULL)
	{
		xpipe(pipefds, info);
		cmd_node(node->left, in_fd, pipefds[1], info);
		return (pipe_node(node->right, pipefds[0], out_fd, info));
	}
	else
	{
		status = builtin_dispatcher(node->left->args, &in_fd, &out_fd, info);
		if (status != E_NOT_BUITIN_CMD)
			return (status);
		pid = cmd_node(node->left, in_fd, out_fd, info);
		if (pid == -1)
			return (E_COMMAND_NOT_FOUND);
		waitpid(pid, &status, 0);
	}
	return ((t_status)status);
}
