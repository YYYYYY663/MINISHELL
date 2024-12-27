#include "ft_executor.h"
#include "ft_system.h"
#include "ft_token.h"
#include <signal.h>
#include "ft_parser.h"
/*
 * CMDの処理はpreでもinでもどこでも大丈夫
 * signal handlingのためにすべてにifcheckをいれるべき
 */

pid_t	cmd_node(t_ast *node, int in_fd, int out_fd, t_info *info)
{
	#ifdef FUNC_OUT
		printf("%s node: %s\n",__func__, e_type_to_str(node->ntype));
	#endif
	pid_t	pid;
	//ここの処理怪しい
	if (node->ntype == NT_PIPE)
		return(cmd_node(node->left, in_fd, out_fd, info));
	
	if (setup_args(node->args, &in_fd, &out_fd, info))
        return -1;
	
	pid = xfork(info);
	if (pid == 0)
	{
		#ifdef FUNC_OUT
			dprintf(2,"in: %d\tout: %d\n",in_fd,out_fd);
		#endif
        xdup2(in_fd, STDIN_FILENO,info);
		xdup2(out_fd, STDOUT_FILENO,info);
		#ifdef FUNC_OUT
			dprintf(2,"in: %d\tout: %d\n",in_fd,out_fd);
		#endif
		execve(node->args->path, node->args->cargv, ft_list_to_strs(info->env_map));
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

t_status pipe_node(t_ast *node, int in_fd, int out_fd, t_info *info)
{
	#ifdef FUNC_OUT
		printf("%s\n",__func__);
	#endif
	int pipefds[2];
	int status = 0;
    pid_t pid;
	if (node->right != NULL)
	{
		xpipe(pipefds, info);
		cmd_node(node->left, in_fd, pipefds[1], info);
		//xclose(&pipefds[1]);
		pipe_node(node->right, pipefds[0], out_fd, info);
		//xclose(&pipefds[0]);
	}
	else
	{
		//todo builtinの確認
		pid = cmd_node(node->left, in_fd, out_fd, info);
        if (pid==-1)
            return E_COMMAND_NOT_FOUND;//fileかもしれない todo
        // kill(pid,SIGTERM)
		waitpid(pid, &status, 0);
		//cmd_node(node->left, in_fd, out_fd, info);
        printf("last command wait status: %d\n", status);
	}
	return ((t_status)status);
}