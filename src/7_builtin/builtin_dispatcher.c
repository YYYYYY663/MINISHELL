/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtinr__dispatcher.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymizukam <ymizukam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 22:00:28 by teando            #+#    #+#             */
/*   Updated: 2024/12/22 16:57:00 by ymizukam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_builtin.h"
#include "ft_system.h"

// ビルトイン関数を実行する
t_status	builtin_dispatcher(char *path, char **argv, t_info *info)
{
	static const char		*builtin_names[] = {"pwd", "cd", "echo", "export",
				"unset", "exit", "env"};
	static t_builtin_func	builtin_funcs[] = {__pwd, __cd,
			__echo, __export, __unset, __exit,
			__env};
	size_t					i;

	i = 0;
	while (i < sizeof(builtin_names) / sizeof(builtin_names[0]))
	{
		if (ft_strncmp(path, builtin_names[i], ft_strlen(path)) == 0)
		{
			return (builtin_funcs[i](path, argv, info));
		}
		i++;
	}
	return (-1); //見つからない場合は他のコマンドを実行するからvoidでも良いかな
}

// int	is_builtin(char *cmd)
// {
// 	if (!cmd)
// 		return (0);
// 	if (!ft_strcmp(cmd, "echo"))
// 		return (1);
// 	if (!ft_strcmp(cmd, "cd"))
// 		return (1);
// 	if (!ft_strcmp(cmd, "pwd"))
// 		return (1);
// 	if (!ft_strcmp(cmd, "export"))
// 		return (1);
// 	if (!ft_strcmp(cmd, "unset"))
// 		return (1);
// 	if (!ft_strcmp(cmd, "env"))
// 		return (1);
// 	if (!ft_strcmp(cmd, "exit"))
// 		return (1);
// 	return (0);
// }

// int	exec_builtin(void)
// {
// 	if (!ft_strcmp(argv[0], "echo"))
// 		return ();
// 	if (!ft_strcmp(argv[0], "cd"))
// 		return ();
// 	if (!ft_strcmp(argv[0], "pwd"))
// 		return (builtin_pwd());
// 	if (!ft_strcmp(argv[0], "export"))
// 		return ();
// 	if (!ft_strcmp(argv[0], "unset"))
// 		return ();
// 	if (!ft_strcmp(argv[0], "env"))
// 		return ();
// 	if (!ft_strcmp(argv[0], "exit"))
// 		return ();
// 	return (127);
// }
