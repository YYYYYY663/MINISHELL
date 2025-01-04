/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _builtin_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymizukam <ymizukam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 15:45:58 by teando            #+#    #+#             */
/*   Updated: 2025/01/04 22:12:39 by ymizukam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_builtin.h"
#include "ft_env.h"
#include "ft_system.h"

static int	_is_number(char *str);

/*
	1,引数が数字ではない
	exit
	bash: exit: 2a: numeric argument required
	2,引数が多い
	bash-3.2$ exit 22 2a
	exit
	bash: exit: too many arguments
*/
t_status	__exit(const char *path, char **argv, t_info *info)
{
	int	exit_status;

	exit_status = 0;
	(void)path;
	printf("exit\n");
	if (argv[1] != NULL)
	{
		// todo xperror早めに作る
		if (!_is_number(argv[1]))
		{
			ft_putstr_fd("numeric argument required\n", STDERR_FILENO);
			system_exit(info, 255);
		}
		else if (argv[2])
		{
			ft_putstr_fd("too many arguments\n", STDERR_FILENO);
			system_exit(info, 255);
		}
		exit_status = ft_atoi(argv[1]);
	}
	system_exit(info, exit_status);
	return (1);
}

static int	_is_number(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '-')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}
