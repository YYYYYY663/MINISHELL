/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   __main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 22:51:27 by teando            #+#    #+#             */
/*   Updated: 2024/12/17 23:31:33 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_system.h"

int	main(int argc, char **argv, char **envp)
{
	t_info	*info;

	printf("%s\n", envp[0]);
	info = system_init(envp);
	// envcp = ft_list_to_strs(info->env_map);
	// ft_putstrs_fd(envcp, "\n", STDOUT_FILENO);
	// ft_strs_clear(envcp);
	// system_exit(info, 0);
}
