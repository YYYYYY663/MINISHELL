/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 15:45:58 by teando            #+#    #+#             */
/*   Updated: 2024/12/17 16:54:48 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_builtin.h"
#include "ft_env.h"
#include "ft_system.h"

t_status	__exit(const char *path, char **argv, t_info *info)
{
	/*
	1,引数が数字ではない
	exit
	bash: exit: 2a: numeric argument required
	2,引数が多い
	bash-3.2$ exit 22 2a
	exit
	bash: exit: too many arguments
	*/
	printf("exit\n");
	system_exit(info,info->status);
	return 1;
}
