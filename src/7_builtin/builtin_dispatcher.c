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
#include "xunistd.h"
#include "ft_redirect.h"

// ビルトイン関数を実行する

int setup_builtin_args(t_args *args, int *in_fd, int *out_fd, t_info *info)
{
	if (redirect_dipacher(args->redr, in_fd, out_fd, info))
    {
        return 1;
    }
	args->cargv = convert_argv(args->argv);
	return 0;
}

t_status	builtin_dispatcher(t_args *args, int *in_fd, int *out_fd, t_info *info)
{
	static const char		*builtin_names[] = \
	{"pwd", "cd", "echo", "export","unset", "exit", "env"};
	static t_builtin_func	builtin_funcs[] = \
	{__pwd, __cd, __echo, __export, __unset, __exit, __env};

	size_t					i;
	t_token *token = (t_token *) args->argv->data;

	i = 0;
	if (*in_fd != STDIN_FILENO || *out_fd != STDOUT_FILENO || token->value == NULL)
		return E_NOT_BUITIN_CMD;
	while (i < sizeof(builtin_names) / sizeof(builtin_names[0]))
	{
		if (ft_strncmp(token->value, builtin_names[i], ft_strlen(token->value)) == 0)
		{
			if (setup_builtin_args(args, in_fd, out_fd, info))
				return E_FILE;
			info->status = builtin_funcs[i](token->value, args->cargv, info);
			xdup2(STDIN_FILENO, *in_fd, info);
			xdup2(STDOUT_FILENO, *out_fd,info);
			return info->status;
		}
		i++;
	}
	return (E_NOT_BUITIN_CMD);
}
