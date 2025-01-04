/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _builtin_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymizukam <ymizukam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 15:45:58 by teando            #+#    #+#             */
/*   Updated: 2025/01/05 02:40:35 by ymizukam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_builtin.h"
#include "ft_env.h"
#include "ft_system.h"

/*
	1,引数が数字ではない
	exit
	bash: exit: 2a: numeric argument required
	2,引数が多い
	bash-3.2$ exit 22 2a
	exit
	bash: exit: too many arguments
*/
t_status	__exit(char **argv, t_info *info)
{
	long	exit_status;
	char	*endptr;

	exit_status = 0;
	printf("exit\n");
	if (argv[1] != NULL)
	{
		exit_status = ft_strtol(argv[1], &endptr, 10);
		if (endptr != argv[1] + ft_strlen(argv[1]) || exit_status > INT_MAX
			|| exit_status < INT_MIN)
		{
			ft_dprintf(2, "minishell: exit: %s: numeric argument required\n",
				argv[1]);
			system_exit(info, 2);
		}
		else if (argv[2])
		{
			ft_putstr_fd("minishell: exit: too many arguments\n",
				STDERR_FILENO);
			return (1);
		}
	}
	system_exit(info, (t_status)exit_status % 0x100);
	return (1);
}
