/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _builtin_unset.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymizukam <ymizukam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 22:13:06 by ymizukam          #+#    #+#             */
/*   Updated: 2025/01/04 22:13:07 by ymizukam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_builtin.h"
#include "ft_env.h"
#include "ft_system.h"

t_status	__unset(const char *path, char **argv, t_info *info)
{
	int	i;

	(void)path;
	i = 0;
	while (argv[i])
	{
		env_unset(argv[i++], info);
	}
	return (E_NONE);
}
