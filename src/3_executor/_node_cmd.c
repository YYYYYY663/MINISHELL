// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   node_cmd.c                                         :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: ymizukam <ymizukam@student.42.fr>          +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2024/12/22 16:32:15 by ymizukam          #+#    #+#             */
// /*   Updated: 2024/12/22 16:44:51 by ymizukam         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "ft_executor.h"
// #include "ft_system.h"
// #include "xunistd.h"

// void	process_cmd_node(t_list *lst, t_info *info)
// {
// 	char	path[PATH_MAX];
// 	pid_t	pid;

// 	// 引数をパース
// 	//変数展開　redirect 絶対パスの取得(access X_OK) fork
// 	if (!lst)
// 		return ;
// 	if (fetch_absolutepath(path, , info->env_path, X_OK))
// 	{
// 		perror(); // bash: argv[0]: command not found
// 		return ;
// 	}
// 	pid = xfork(info);
// 	if (pid == -1)
// 	{
// 		perror("fork");
// 		system_exit(info, errno);
// 	}
// 	else if (pid == 0) // 子プロセス
// 	{
// 		execve(path, argv, info->env);
// 		perror("execve");
// 		// ft_strs_clear(argv);//need ?
// 		exit(errno); // exit status?
// 	}
// 	//親プロセス
// }
