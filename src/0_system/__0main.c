/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   __0main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymizukam <ymizukam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 22:51:27 by teando            #+#    #+#             */
/*   Updated: 2025/01/04 21:31:00 by ymizukam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_system.h"

int	main(int argc, char **argv, char **envp)
{
	t_info	*info;

	info = system_init(envp);
	system_exit(info, 0);
}
