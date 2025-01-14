/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   __main_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymizukam <ymizukam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 22:06:46 by ymizukam          #+#    #+#             */
/*   Updated: 2025/01/14 17:03:32 by ymizukam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_env.h"
#include "ft_system.h"

int	main(int argc, char **argv, char **envp)
{
	t_info	*info;
	char	*home;

	(void)argc;
	(void)argv;
	info = system_init(envp);
	home = env_get("HOME", info);
	printf("before unset: %s\n", home);
	free(home);
	map_unset("HOME", info);
	home = env_get("HOME", info);
	printf("after  unset: %s\n", home);
	free(home);
	// map_export("NEW_KEY=gokigennikaga!!",info);
	// printf("export: %s\n",env_get("NEW_KEY",info));
	// map_export("KEY=",info);
	// map_export("NOEQUAL",info);
	// printf("export: %s\n",env_get("KEY",info));
	// printf("NOEQUAL: %s\n",env_get("NOEQUAL",info));
	// printf("NOTEXIST: %s\n",env_get("NOTEXIST",info));
	map_export("KEY=a", info);
	map_export("KEYERR =", info);
	map_export("1KEYERR=", info);
	system_exit(info, 0);
}
