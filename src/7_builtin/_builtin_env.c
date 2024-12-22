/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _builtin_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymizukam <ymizukam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 15:47:05 by teando            #+#    #+#             */
/*   Updated: 2024/12/22 16:58:43 by ymizukam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_builtin.h"
// #include "ft_env.h"
#include "ft_system.h"

t_status	__env(const char *path, char **argv, t_info *info)
{
	char	**envp;

	envp = xlst_to_strs(info->env_map, info);
	(void)path;
	(void)argv;
	ft_putstrs_fd(envp, "\n", STDOUT_FILENO);
	ft_strs_clear(envp);
	return (E_NONE);
}
