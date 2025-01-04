#include "ft_system.h"
#include <stdio.h>

int	main(int argc, char **argv, char **env)
{
	t_info *info = system_init(env);

	system_exit(info, 0);

	return (0);
}